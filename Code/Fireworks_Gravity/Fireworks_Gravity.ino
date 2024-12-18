
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Screen dimensions
const int SCREEN_WIDTH = 280;
const int SCREEN_HEIGHT = 240;

// Ball properties
const int BALL_RADIUS = 3;
const float GRAVITY = 0.1; // Softer gravity effect
const int TOP_MARGIN = 50; // Pixels from the top
const int DROP_DISTANCE = 150; // Max drop distance for particles
const int PARTICLE_LIFETIME = 2000; // Lifetime of particles in milliseconds

struct FireworkParticle {
  float x, y;
  float velocityX, velocityY;
  bool active;
  float startY; // Initial Y position to track drop distance
  unsigned long startTime; // Time when the particle was activated
  uint16_t color; // Color of the particle
  float alpha; // Opacity level for dissolving effect
};

FireworkParticle particles[50];
float ballX, ballY;
float velocityX, velocityY;
bool stopped = false; // Flag to indicate when the ball stops
bool exploded = false; // Flag to indicate when the ball explodes
uint16_t ballColor = TFT_WHITE; // Color of the ball

void setup() {
  tft.init();
  tft.setRotation(1); // Adjust screen orientation if needed
  tft.fillScreen(TFT_BLACK);

  resetBall();
}

void loop() {
  if (exploded) {
    // Update particles
    bool anyActive = false;
    for (int i = 0; i < 50; i++) {
      if (particles[i].active) {
        unsigned long currentTime = millis();
        // Calculate elapsed time
        unsigned long elapsedTime = currentTime - particles[i].startTime;

        // Deactivate particle if it exceeds lifetime
        if (elapsedTime >= PARTICLE_LIFETIME) {
          particles[i].active = false;
          continue;
        }

        anyActive = true;
        // Clear previous position
        tft.fillCircle(particles[i].x, particles[i].y, BALL_RADIUS / 2, TFT_BLACK);

        // Update position
        particles[i].x += particles[i].velocityX;
        particles[i].y += particles[i].velocityY;

        // Apply gravity
        particles[i].velocityY += GRAVITY;

        // Reduce opacity over time to create a dissolving effect
        particles[i].alpha = 1.0 - (float(elapsedTime) / PARTICLE_LIFETIME);
        uint16_t fadedColor = applyAlphaToColor(particles[i].color, particles[i].alpha);

        // Draw particle with reduced opacity
        tft.fillCircle(particles[i].x, particles[i].y, BALL_RADIUS / 2, fadedColor);
      }
    }

    // If no particles are active, reset the ball
    if (!anyActive) {
      resetBall();
    }

    delay(30);
    return;
  }

  // Clear the previous position of the ball
  tft.fillCircle(ballX, ballY, BALL_RADIUS, TFT_BLACK);

  if (!stopped) {
    // Update ball position
    ballX += velocityX;
    ballY += velocityY;

    // Apply gravity
    velocityY -= GRAVITY;

    // Gradually slow down significantly as it approaches the top
    if (ballY <= TOP_MARGIN + 50) { // Begin reducing speed earlier
      velocityY *= 0.92; // More noticeable slow down effect
    }

    // Check if the ball reaches the top margin
    if (ballY <= TOP_MARGIN) {
      ballY = TOP_MARGIN; // Snap to the top margin
      velocityY = 0; // Stop upward motion
      stopped = true; // Ball stops here
      explode();
    }
  }

  // Draw the ball at its new position
  tft.fillCircle(ballX, ballY, BALL_RADIUS, ballColor);

  // Small delay for smoother animation
  delay(30);
}

void resetBall() {
  // Start at the bottom center of the screen
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT - BALL_RADIUS;

  // Give the ball a slight random horizontal velocity
  velocityX = random(-1, 2) * 0.5; // Further reduced horizontal speed

  // Set an initial upward velocity with less speed
  velocityY = -random(5, 8); // Random value between -5 and -8 for slower launch

  // Reset stopped and exploded flags
  stopped = false;
  exploded = false;
}

void explode() {
  exploded = true;

  for (int i = 0; i < 50; i++) {
    particles[i].x = ballX;
    particles[i].y = ballY;
    particles[i].startY = ballY; // Record the initial Y position
    particles[i].velocityX = random(-30, 30) * 0.1; // Random horizontal velocity
    particles[i].velocityY = random(-20, 0) * 0.1;  // Random vertical velocity
    particles[i].active = true;
    particles[i].startTime = millis(); // Record the activation time
    particles[i].color = randomColor(); // Assign a random color to each particle
    particles[i].alpha = 1.0; // Start fully opaque
  }
}

uint16_t randomColor() {
  // Generate a random RGB565 color
  return tft.color565(random(0, 256), random(0, 256), random(0, 256));
}

uint16_t applyAlphaToColor(uint16_t color, float alpha) {
  // Extract RGB components from RGB565 color
  uint8_t r = (color >> 11) & 0x1F;
  uint8_t g = (color >> 5) & 0x3F;
  uint8_t b = color & 0x1F;

  // Apply alpha to each component
  r = r * alpha;
  g = g * alpha;
  b = b * alpha;

  // Reconstruct RGB565 color
  return tft.color565(r << 3, g << 2, b << 3);
}
