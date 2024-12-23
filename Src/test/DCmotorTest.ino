#include <CytronMotorDriver.h>

// Motor Driver configuration
#define MOTOR_PWM_PIN 5   // PWM pin for controlling motor speed
#define MOTOR_DIR_PIN 4   // Motor direction pin

// Create an instance of the motor driver
CytronMD motor(PWM_DIR, MOTOR_PWM_PIN, MOTOR_DIR_PIN);

// Variables to store motor state
int motorSpeed = 0;
String inputString = "";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize motor (stopped)
  motor.setSpeed(0);
  
  // Print instructions
  Serial.println("Simple DC Motor Control Ready");
  Serial.println("Command: sXXX - Set motor speed (-255 to 255)");
}

void loop() {
  // Process serial input when complete command is received
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      processCommand(inputString);
      inputString = "";
    } else {
      inputString += inChar;
    }
  }
}

void processCommand(String command) {
  command.trim();  // Remove any whitespace
  
  if (command.startsWith("s")) {
    // Extract speed value from command
    int newSpeed = command.substring(1).toInt();
    
    // Constrain speed value to valid range
    newSpeed = constrain(newSpeed, -255, 255);
    
    // Set motor speed using Cytron library
    motor.setSpeed(newSpeed);
    Serial.println("Motor speed set to: " + String(newSpeed));
  } else {
    Serial.println("Invalid command. Use sXXX where XXX is between -255 and 255");
  }
}