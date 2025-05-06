// Combined TFT Clock and Bouncing Balls
// Displays time in foreground with animated falling balls in background
// Uses TFT_eSPI, ESP32Time, WiFi, NeoPixel

#include <TFT_eSPI.h>
#include <ESP32Time.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
#include "Smaller_DotFont.h" 
#include "DotFont.h"

// PIN definitions
#define LED_PIN 8
#define NUMPIXELS 1

//PWM Backlight 
int ledPin = 7;


// WiFi credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* ntpServer = "pool.ntp.org";

// Time sync intervals
const unsigned long SYNC_INTERVAL = 300000;  // 5 minutes in milliseconds
const unsigned long SAVE_INTERVAL = 3600000; // 1 hour in milliseconds

// Screen dimensions
const int screenWidth = 280;
const int screenHeight = 240;

// Objects
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite timeSprite = TFT_eSprite(&tft);  // Sprite for time display
Adafruit_NeoPixel pixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Preferences preferences;
ESP32Time rtc(-3 * 3600);  // -3 hours timezone in seconds

// Time variables
bool timeEverSynced = false;
time_t lastValidTime = 0;
unsigned long lastTimeSync = 0;
unsigned long lastTimeSave = 0;
unsigned long lastTimeUpdate = 0;

// Day and month names
const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12] = {"Jan", "Feb", "March", "April", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};

// Ball properties
const int maxBalls = 15;    // Maximum number of active balls (reduced from 50)
const int ballRadius = 4;   // Radius of each ball
const float gravity = 0.5;  // Gravity acceleration
const float damping = 0.5;  // Bounce damping factor with the bottom
const float collisionDamping = 0.8; // Damping factor for ball-to-ball collisions
const int ballLifetime = 5000; // Lifetime of a ball in milliseconds

struct Ball {
  float x;             // Horizontal position
  float y;             // Vertical position
  float vx;            // Horizontal velocity
  float vy;            // Vertical velocity
  uint16_t color;      // Ball color
  unsigned long startTime; // Time when the ball started falling
  bool active;         // Is the ball active?
};

// Array to store the balls
Ball balls[maxBalls];

// Forward declarations
void drawTime();
void setLED(uint8_t r, uint8_t g, uint8_t b);
void initializeBalls();
void spawnBall();
void handleCollisions();
void updateBalls();

void setup() {
  Serial.begin(115200);
  pixel.begin();
  setLED(50, 50, 50);  // Yellow during initialization
  
  // Initialize display
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  //PWM Backlight
  analogWrite(ledPin, 80);
 
  // Create sprite for time display (transparent overlay)
  timeSprite.createSprite(280, 240);
  timeSprite.setColorDepth(8);  //8
  
  // Initialize balls
  initializeBalls();
  
  // Load saved time from flash
  loadTimeFromPreferences();
  
  // Initial WiFi connection and time sync
  connectAndSyncTime();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Update balls physics simulation every 20ms
  static unsigned long lastBallUpdate = 0;
  if (currentMillis - lastBallUpdate >= 20) {
    // Spawn a new ball occasionally
    if (random(0, 20) < 2) { // Reduced spawn rate
      spawnBall();
    }
    
    // Handle collisions between balls
    handleCollisions();
    
    // Update and draw all active balls
    updateBalls();
    
    lastBallUpdate = currentMillis;
  }
  
  // Update time display every 100ms
  if (currentMillis - lastTimeUpdate >= 100) {
    drawTime();
    lastTimeUpdate = currentMillis;
  }
  
  // Save time to flash periodically if it has been synced at least once
  if (timeEverSynced && (currentMillis - lastTimeSave > SAVE_INTERVAL)) {
    // Don't save if it looks like default time (Jan 1, 12:00)
    if (!(rtc.getMonth() == 0 && rtc.getDay() == 1 && rtc.getHour() == 12 && rtc.getMinute() == 0)) {
      saveTimeToPreferences();
      lastTimeSave = currentMillis;
    }
  }
  
  // Try to sync time every 5 minutes
  if (currentMillis - lastTimeSync > SYNC_INTERVAL) {
    connectAndSyncTime();
    lastTimeSync = currentMillis;
  }
}

// Ball-related functions
void initializeBalls() {
  for (int i = 0; i < maxBalls; i++) {
    balls[i].active = false; // Initially, no balls are active
  }
}

void spawnBall() {
  for (int i = 0; i < maxBalls; i++) {
    if (!balls[i].active) {
      balls[i].x = screenWidth / 2 + random(-12, 13) * ballRadius; // Random position within 25 pixels
      balls[i].y = 0; // Start at the top
      balls[i].vx = random(-2, 3) * 0.5; // Random horizontal velocity
      balls[i].vy = 0; // Initial vertical velocity
      
      // Only allow 1-2 color components to be high
      uint8_t r = random(0, 2) ? random(200, 255) : random(0, 50);
      uint8_t g = random(0, 2) ? random(200, 255) : random(0, 50);
      uint8_t b = random(0, 2) ? random(200, 255) : random(0, 50);
      balls[i].color = tft.color565(r, g, b);
      
      balls[i].startTime = millis(); // Record the start time
      balls[i].active = true; // Mark the ball as active
      break;
    }
  }
}

void handleCollisions() {
  for (int i = 0; i < maxBalls; i++) {
    if (!balls[i].active) continue;

    for (int j = i + 1; j < maxBalls; j++) {
      if (!balls[j].active) continue;

      // Calculate the distance between the balls
      float dx = balls[j].x - balls[i].x;
      float dy = balls[j].y - balls[i].y;
      float distance = sqrt(dx * dx + dy * dy);

      if (distance < 2 * ballRadius) { // Collision detected
        // Normalize the collision vector
        float nx = dx / distance;
        float ny = dy / distance;

        // Relative velocity
        float vx = balls[j].vx - balls[i].vx;
        float vy = balls[j].vy - balls[i].vy;

        // Velocity along the normal
        float dotProduct = vx * nx + vy * ny;

        if (dotProduct > 0) continue; // Balls are moving apart

        // Apply collision response with damping
        float impulse = (1 + collisionDamping) * dotProduct / 2; // Scale impulse

        balls[i].vx += impulse * nx;
        balls[i].vy += impulse * ny;
        balls[j].vx -= impulse * nx;
        balls[j].vy -= impulse * ny;
      }
    }
  }
}

void updateBalls() {
  unsigned long currentTime = millis();

  for (int i = 0; i < maxBalls; i++) {
    if (balls[i].active) {
      // Check if the ball's lifetime has elapsed
      if (currentTime - balls[i].startTime > ballLifetime) {
        // Erase the ball and deactivate it
        tft.fillCircle(balls[i].x, balls[i].y, ballRadius, TFT_BLACK);
        balls[i].active = false;
        continue;
      }

      // Clear the previous ball position
      tft.fillCircle(balls[i].x, balls[i].y, ballRadius, TFT_BLACK);

      // Apply gravity
      balls[i].vy += gravity;

      // Update position
      balls[i].x += balls[i].vx;
      balls[i].y += balls[i].vy;

      // Check for collision with screen edges
      if (balls[i].x - ballRadius < 0 || balls[i].x + ballRadius > screenWidth) {
        balls[i].vx = -balls[i].vx; // Reverse horizontal velocity
        
        // Keep ball in bounds
        if (balls[i].x - ballRadius < 0) balls[i].x = ballRadius;
        if (balls[i].x + ballRadius > screenWidth) balls[i].x = screenWidth - ballRadius;
      }
      
      if (balls[i].y + ballRadius >= screenHeight) {
        balls[i].y = screenHeight - ballRadius; // Reset position to just above the bottom
        balls[i].vy = -balls[i].vy * damping; // Reverse and reduce vertical velocity for bounce

        // Stop bouncing if velocity is negligible
        if (abs(balls[i].vy) < 1) {
          balls[i].vy = 0;
        }
      }

      // Draw the ball at its new position
      tft.fillCircle(balls[i].x, balls[i].y, ballRadius, balls[i].color);
    }
  }
}

// LED helper function
void setLED(uint8_t r, uint8_t g, uint8_t b) {
  pixel.clear();
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

// Time-related functions
void drawTime() {
  // Clear the time sprite with transparency
  //timeSprite.fillSprite(TFT_TRANSPARENT);  //Doesnt work well
  timeSprite.fillSprite(TFT_BLACK);
  
  // Format time components
  String hourStr = String(rtc.getHour());
  String minStr = (rtc.getMinute() < 10) ? "0" + String(rtc.getMinute()) : String(rtc.getMinute());
  String secStr = (rtc.getSecond() < 10) ? "0" + String(rtc.getSecond()) : String(rtc.getSecond());
  
  // Draw time (left-aligned) with shadow for visibility over balls
  timeSprite.loadFont(DotFont);
  
  int xPos = 40;
  int yPos = 100;
  
  // Draw time with shadow for better visibility over balls
  // First draw shadow
  timeSprite.setTextColor(TFT_BLACK);
  
  // Draw hour:minute:second shadows
  timeSprite.drawString(hourStr, xPos+2, yPos+2);
  xPos += timeSprite.textWidth(hourStr) + 5;
  
  timeSprite.drawString(".", xPos+2, yPos+2);
  xPos += timeSprite.textWidth(".") + 5;
  
  timeSprite.drawString(minStr, xPos+2, yPos+2);
  xPos += timeSprite.textWidth(minStr) + 5;
  
  timeSprite.drawString(".", xPos+2, yPos+2);
  xPos += timeSprite.textWidth(".") + 5;
  
  timeSprite.drawString(secStr, xPos+2, yPos+2);
  
  // Reset position for actual text
  xPos = 40;
  
  // Now draw actual text in green
  timeSprite.setTextColor(TFT_GREEN);
  
  // Draw hour:minute:second
  timeSprite.drawString(hourStr, xPos, yPos);
  xPos += timeSprite.textWidth(hourStr) + 5;
  
  timeSprite.drawString(".", xPos, yPos);
  xPos += timeSprite.textWidth(".") + 5;
  
  timeSprite.drawString(minStr, xPos, yPos);
  xPos += timeSprite.textWidth(minStr) + 5;
  
  timeSprite.drawString(".", xPos, yPos);
  xPos += timeSprite.textWidth(".") + 5;
  
  timeSprite.drawString(secStr, xPos, yPos);
  
  // Draw date and day with semi-transparent background for better readability
  timeSprite.loadFont(Smaller_DotFont);
  
  // Draw background rectangles for better readability
  timeSprite.fillRect(15, 20, 100, 30, TFT_BLACK);
  timeSprite.fillRect(145, 20, 120, 30, TFT_BLACK);
  
  // Date text
  timeSprite.setTextColor(TFT_WHITE);
  timeSprite.drawString(days[rtc.getDayofWeek()], 20, 24);
  timeSprite.drawString(months[rtc.getMonth()] + " " + String(rtc.getDay()), 150, 24);
  
  // Show if time has never been synced
  if (!timeEverSynced) {
    timeSprite.fillRect(35, 175, 210, 30, TFT_BLACK);
    timeSprite.drawString("Time not synced", 40, 180);
  }
  
  timeSprite.unloadFont();
  
  // Push sprite with transparency
  timeSprite.pushSprite(0, 0, TFT_TRANSPARENT);
}

// Combined WiFi connection and time sync
void connectAndSyncTime() {
  // Skip connection attempt if already connected
  if (WiFi.status() != WL_CONNECTED) {
    setLED(100, 0, 0);  // Red during connection attempt
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    // Wait for connection for up to 10 seconds
    unsigned long startAttempt = millis();
    bool showDot = false;
    
    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000) {
      // Show connecting animation
      drawTime();
      
      timeSprite.loadFont(Smaller_DotFont);
      timeSprite.fillRect(55, 205, 170, 30, TFT_BLACK);
      timeSprite.setTextColor(TFT_YELLOW);
      timeSprite.drawString(showDot ? "Connecting ." : "Connecting", 60, 210);
      timeSprite.unloadFont();
      timeSprite.pushSprite(0, 0);
      
      showDot = !showDot;
      delay(500);
    }
  }
  
  // Try to sync time if connected
  if (WiFi.status() == WL_CONNECTED) {
    setLED(0, 0, 100);  // Blue during time sync
    
    // Configure NTP
    configTime(0, 0, ntpServer);
    
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      // Validate the time isn't the suspicious default (Jan 1, 12:00)
      if (timeinfo.tm_mon == 0 && timeinfo.tm_mday == 1 && 
          timeinfo.tm_hour == 12 && timeinfo.tm_min == 0) {
        // Keep previous valid time if available
        if (lastValidTime > 1672531200) { // After Jan 1, 2023
          setLED(0, 0, 50);  // Yellow - keeping old time
          return;
        }
      }
      
      // Update RTC with valid time
      rtc.setTimeStruct(timeinfo);
      timeEverSynced = true;
      saveTimeToPreferences();
      
      // Show success message
      drawTime();
      timeSprite.loadFont(Smaller_DotFont);
      timeSprite.fillRect(65, 205, 150, 30, TFT_BLACK);
      timeSprite.setTextColor(TFT_GREEN);
      timeSprite.drawString("Time synced!", 70, 210);
      timeSprite.unloadFont();
      timeSprite.pushSprite(0, 0);
      setLED(0, 20, 0);  // Green for successful sync
      delay(1000);
    } else {
      // Show failure message
      drawTime();
      timeSprite.loadFont(Smaller_DotFont);
      timeSprite.fillRect(65, 205, 150, 30, TFT_BLACK);
      timeSprite.setTextColor(TFT_RED);
      timeSprite.drawString("Sync failed", 70, 210);
      timeSprite.unloadFont();
      timeSprite.pushSprite(0, 0);
      setLED(50, 0, 0);  // Red for failed sync
      delay(1000);
    }
  } else {
    // WiFi connection failed
    setLED(50, 0, 0);  // Red for connection failure
  }
}

// Save time to flash memory
void saveTimeToPreferences() {
  preferences.begin("clocktime", false);
  time_t currentEpoch = rtc.getEpoch();
  preferences.putULong("lastTime", currentEpoch);
  preferences.end();
  
  lastValidTime = currentEpoch;
}

// Load time from flash memory
void loadTimeFromPreferences() {
  preferences.begin("clocktime", true);
  time_t savedTime = preferences.getULong("lastTime", 0);
  preferences.end();
  
  // Only use saved time if it's reasonably valid (after year 2023)
  if (savedTime > 1672531200) { // Jan 1, 2023
    rtc.setTime(savedTime);
    lastValidTime = savedTime;
    timeEverSynced = true;
  }
}

/*
void setBrightness(uint8_t value)
{
 static uint8_t level = 0;
 static uint8_t steps = 16;
 int from = steps - level;
 int to = steps - value;
 int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++) 
    {
     digitalWrite(TFT_BL, 0);
     digitalWrite(TFT_BL, 1);
    }
    level = value;
}
*/
 