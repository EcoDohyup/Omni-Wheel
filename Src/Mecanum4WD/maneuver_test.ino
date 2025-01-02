#include <Arduino.h>

// Pin definitions for motor control
// motor1 - Front Left
#define DIR1 27
#define PWM1 14
// motor2 - Front Right
#define DIR2 12
#define PWM2 13
// motor3 - Rear Left
#define DIR3 35
#define PWM3 32
// motor4 - Rear Right
#define DIR4 33
#define PWM4 25

#define PWM_MAX 255      // Maximum PWM value
int baseSpeed = 200;     // Default speed for movements

// Function to control individual motor
void setMotor(int dirPin, int pwmPin, bool direction, int speed) {
  digitalWrite(dirPin, direction);
  analogWrite(pwmPin, speed);
}

// Stop all motors
void stopMotors() {
  setMotor(DIR1, PWM1, HIGH, 0);
  setMotor(DIR2, PWM2, HIGH, 0);
  setMotor(DIR3, PWM3, HIGH, 0);
  setMotor(DIR4, PWM4, HIGH, 0);
}

// Mecanum movement functions
void moveForward(int speed) {
  setMotor(DIR1, PWM1, HIGH, speed);  // Front Left
  setMotor(DIR2, PWM2, HIGH, speed);  // Front Right
  setMotor(DIR3, PWM3, HIGH, speed);  // Rear Left
  setMotor(DIR4, PWM4, HIGH, speed);  // Rear Right
}

void moveBackward(int speed) {
  setMotor(DIR1, PWM1, LOW, speed);
  setMotor(DIR2, PWM2, LOW, speed);
  setMotor(DIR3, PWM3, LOW, speed);
  setMotor(DIR4, PWM4, LOW, speed);
}

void moveRight(int speed) {
  setMotor(DIR1, PWM1, HIGH, speed);  // Front Left forward
  setMotor(DIR2, PWM2, LOW, speed);   // Front Right backward
  setMotor(DIR3, PWM3, LOW, speed);   // Rear Left backward
  setMotor(DIR4, PWM4, HIGH, speed);  // Rear Right forward
}

void moveLeft(int speed) {
  setMotor(DIR1, PWM1, LOW, speed);   // Front Left backward
  setMotor(DIR2, PWM2, HIGH, speed);  // Front Right forward
  setMotor(DIR3, PWM3, HIGH, speed);  // Rear Left forward
  setMotor(DIR4, PWM4, LOW, speed);   // Rear Right backward
}

void rotateClockwise(int speed) {
  setMotor(DIR1, PWM1, HIGH, speed);  // Front Left forward
  setMotor(DIR2, PWM2, LOW, speed);   // Front Right backward
  setMotor(DIR3, PWM3, HIGH, speed);  // Rear Left forward
  setMotor(DIR4, PWM4, LOW, speed);   // Rear Right backward
}

void rotateCounterClockwise(int speed) {
  setMotor(DIR1, PWM1, LOW, speed);   // Front Left backward
  setMotor(DIR2, PWM2, HIGH, speed);  // Front Right forward
  setMotor(DIR3, PWM3, LOW, speed);   // Rear Left backward
  setMotor(DIR4, PWM4, HIGH, speed);  // Rear Right forward
}

void moveDiagonal45(int speed) {
  setMotor(DIR1, PWM1, HIGH, speed);  // Front Left forward
  setMotor(DIR2, PWM2, HIGH, 0);      // Front Right stop
  setMotor(DIR3, PWM3, HIGH, 0);      // Rear Left stop
  setMotor(DIR4, PWM4, HIGH, speed);  // Rear Right forward
}

void moveDiagonal135(int speed) {
  setMotor(DIR1, PWM1, HIGH, 0);      // Front Left stop
  setMotor(DIR2, PWM2, HIGH, speed);  // Front Right forward
  setMotor(DIR3, PWM3, HIGH, speed);  // Rear Left forward
  setMotor(DIR4, PWM4, HIGH, 0);      // Rear Right stop
}

void setup() {
  // Configure all pins as outputs
  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR3, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(DIR4, OUTPUT);
  pinMode(PWM4, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  // Test sequence of movements
  Serial.println("Starting movement sequence...");
  
  // Forward
  Serial.println("Moving Forward");
  moveForward(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Backward
  Serial.println("Moving Backward");
  moveBackward(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Right
  Serial.println("Moving Right");
  moveRight(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Left
  Serial.println("Moving Left");
  moveLeft(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Rotate Clockwise
  Serial.println("Rotating Clockwise");
  rotateClockwise(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Rotate Counter-Clockwise
  Serial.println("Rotating Counter-Clockwise");
  rotateCounterClockwise(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Diagonal 45
  Serial.println("Moving Diagonal 45°");
  moveDiagonal45(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
  
  // Diagonal 135
  Serial.println("Moving Diagonal 135°");
  moveDiagonal135(baseSpeed);
  delay(2000);
  stopMotors();
  delay(1000);
}