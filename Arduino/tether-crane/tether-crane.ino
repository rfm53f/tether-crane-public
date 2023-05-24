
#include <AccelStepper.h>

#define STEPPER_EN_PIN 8
#define AXIS_X_POT_PIN A0
#define AXIS_Y_POT_PIN A1

#define STEPPER_X_STEP_PIN 2
#define STEPPER_X_DIR_PIN 5

#define STEPPER_Y_STEP_PIN 3
#define STEPPER_Y_DIR_PIN 6

// Define some steppers and the pins the will use
AccelStepper axisX(AccelStepper::DRIVER, STEPPER_X_STEP_PIN, STEPPER_X_DIR_PIN);
AccelStepper axisY(AccelStepper::DRIVER, STEPPER_Y_STEP_PIN, STEPPER_Y_DIR_PIN);

bool _lastDeflectX;
bool _lastDeflectY;

void setup()
{
  pinMode(STEPPER_EN_PIN, OUTPUT);

  axisX.setMaxSpeed(2000.0);
  axisX.setAcceleration(200.0);
  
  axisY.setMaxSpeed(4000.0);
  axisY.setAcceleration(2000.0);

  digitalWrite(STEPPER_EN_PIN, 0); // Enable stepper motors
}

void loop()
{
  int potX = analogRead(AXIS_X_POT_PIN) - 512;
  int potY = analogRead(AXIS_Y_POT_PIN) - 512;

  bool deflectX = abs(potX) > 5;
  if (deflectX) {
    axisX.setMaxSpeed(potX * 2.0);
    axisX.runSpeedAccel(potX > 0);
  }
  else {
    if (_lastDeflectX) {
      axisX.stop();
    }
    axisX.run();
  }
  
  bool deflectY = abs(potY) > 5;
  if (deflectY) {
    axisY.setMaxSpeed(potY * 4.0);
    axisY.runSpeedAccel(potY > 0);
  }
  else {
    if (_lastDeflectY) {
      axisY.stop();
    }
    axisY.run();
  }

  _lastDeflectX = deflectX;
  _lastDeflectY = deflectY;
}
