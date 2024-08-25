#include <Servo.h>

Servo myServo;  // Create a Servo object

const int limitSwitchPin = 13;  // Define the pin for the limit switch
bool isAtZero = true;  // Track the position of the servo

void setup() {
  myServo.attach(9);  // Attach the servo to pin 9
  pinMode(limitSwitchPin, INPUT_PULLUP);  // Set the limit switch pin as input with internal pull-up resistor
  
  // Start at 0 degrees
  myServo.write(0);
  delay(1000);  // Give the servo some time to reach the position
}

void loop() {
  // Wait for the limit switch to be pressed
  if (digitalRead(limitSwitchPin) == LOW) {  // LOW means the button is pressed
    delay(50);  // Debounce delay to prevent multiple triggers due to bouncing
    
    // Wait for the button to be released
    while (digitalRead(limitSwitchPin) == LOW);

    // Move based on the current position
    if (isAtZero) {
      // Move slowly to 90 degrees
      for (int pos = 0; pos <= 80; pos += 1) {
        myServo.write(pos);
        delay(15);  // Adjust the delay for speed control
      }
      isAtZero = false;  // Update position state
    } else {
      // Move slowly back to 0 degrees
      for (int pos = 90; pos >= 0; pos -= 1) {
        myServo.write(pos);
        delay(15);  // Adjust the delay for speed control
      }
      isAtZero = true;  // Update position state
    }
    
    // Debounce delay after the move
    delay(500);
  }
}