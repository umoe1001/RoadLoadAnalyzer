#include <Stepper.h>

const int stepsPerRevolution = 512; // steps per revolution

// initialize the stepper library on pins 12, 14, 27, 26:
Stepper myStepper(stepsPerRevolution, 12, 14, 27, 26);

unsigned long previousMillis = 0;
const unsigned long runDuration = 135000; // 
const unsigned long pauseDuration = 4000; // 4000 ms = 4 seconds

void setup() {
  myStepper.setSpeed(40); // set the speed to 40 RPM
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Run motor for 3 minutes
  if (currentMillis - previousMillis < runDuration) {
    Serial.println("Clockwise");
    myStepper.step(-stepsPerRevolution);
  }
  // Pause for 3 seconds
  else if (currentMillis - previousMillis < runDuration + pauseDuration) {
    Serial.println("Paused for 3 seconds");
    delay(100);
  } 
  else {
    // Reset the timer after the pause
    previousMillis = currentMillis;
  }
}
