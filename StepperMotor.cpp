#include "StepperMotor.h"

StepperMotor::StepperMotor(int stepPin, int dirPin, float stepsPerRev, int homeDirection)
    : stepPin(stepPin), dirPin(dirPin), stepsPerRevolution(stepsPerRev), homeDirection(homeDirection), lastTarget(0) {
}

void StepperMotor::init() {
    Logger::log(LOG_INFO, "Initializing StepperMotor on pins " + String(stepPin) + " and " + String(dirPin));
    stepper.connectToPins(stepPin, dirPin);
    stepper.setStepsPerRevolution(stepsPerRevolution);
	stepper.setDirectionToHome(homeDirection);
    lastTarget = 0;
}

void StepperMotor::moveAbsolute(float targetDeg) {
    float targetRev = targetDeg / 360.0;
    lastTarget = targetDeg;
    Logger::log(LOG_INFO, "Moving to " + String(targetDeg, 2) + "° (" + String(targetRev, 3) + " rev)");
    stepper.moveToPositionInRevolutions(targetRev);
}

void StepperMotor::moveRelative(float deltaDeg) {
    float currentDeg = getPosition();
    float newTarget = currentDeg + deltaDeg;
    Logger::log(LOG_INFO, "Relative move: current " + String(currentDeg, 2) +
                "°, delta " + String(deltaDeg, 2) + "°, new target " + String(newTarget, 2) + "°");
    moveAbsolute(newTarget);
}

float StepperMotor::getPosition() {
    float rev = stepper.getCurrentPositionInRevolutions();
    float deg = rev * 360.0;
    Logger::log(LOG_DEBUG, "Current position: " + String(deg, 2) + "°");
    return deg;
}

void StepperMotor::setOrigin() {
    stepper.setCurrentPositionAsHomeAndStop();
	//stepper.setCurrentPositionInRevolutions(0);
    lastTarget = 0;
    Logger::log(LOG_INFO, "Origin set to 0°");
}

bool StepperMotor::isMoving() {
    //float current = getPosition();
    //return fabs(current - lastTarget) > 0.5;
	return !stepper.motionComplete();
}

void StepperMotor::stop() {
    Logger::log(LOG_WARN, "Stop function not implemented for StepperMotor");
	stepper.setTargetPositionToStop();
}

void StepperMotor::release() {
    Logger::log(LOG_INFO, "StepperMotor on pins " + String(stepPin) + " released");
	//void setEnablePin(signed char enablePin, byte activeState = ESP_FlexyStepper::ACTIVE_LOW);
	//disableDriver
}

void StepperMotor::lock() {
    Logger::log(LOG_INFO, "StepperMotor on pins " + String(stepPin) + " locked");
	//isDriverEnabled
}

void StepperMotor::setSpeed(float speedDegPerSec) {
    // Переводим скорость из градусов/с в обороты/с (360° = 1 оборот)
    float speedRevPerSec = speedDegPerSec / 360.0;
    stepper.setSpeedInRevolutionsPerSecond(speedRevPerSec);
    Logger::log(LOG_INFO, "StepperMotor speed set to " + String(speedDegPerSec) + "°/s");
}

void StepperMotor::setAcceleration(float accelDegPerSec2) {
    // Переводим ускорение из градусов/с² в обороты/с²
    float accelRevPerSec2 = accelDegPerSec2 / 360.0;
    stepper.setAccelerationInRevolutionsPerSecondPerSecond(accelRevPerSec2);
    Logger::log(LOG_INFO, "StepperMotor acceleration set to " + String(accelDegPerSec2) + "°/s²");
}
