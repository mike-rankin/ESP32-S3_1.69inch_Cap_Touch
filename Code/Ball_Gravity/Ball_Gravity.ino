#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Screen dimensions
const int screenWidth = 280;
const int screenHeight = 240;

// Ball properties
const int maxBalls = 50;    // Maximum number of active balls
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
      balls[i].color = random(0xFFFF); // Random color
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

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  initializeBalls();
}

void loop() {
  // Spawn a new ball periodically
  if (random(0, 10) < 2) { // Random chance to spawn a ball (adjust spawn rate)
    spawnBall();
  }

  // Handle collisions between balls
  handleCollisions();

  // Update and draw all active balls
  updateBalls();

  // Slow down the simulation for smoother animation
  delay(20);
}
