#include "Uln2003Stepper.h"
#include "Config.h"

Uln2003Stepper::Uln2003Stepper()
    // Инициализация AccelStepper в режиме FULL4WIRE с подключением к пинам ULN2003
    : stepper(AccelStepper::FULL4WIRE, ULN2003_IN1, ULN2003_IN3, ULN2003_IN2, ULN2003_IN4), lastTarget(0) {
}

void Uln2003Stepper::init() {
    Logger::log(LOG_INFO, "Initializing Uln2003Stepper (Cap Picker)");
    stepper.setMaxSpeed(ULN2003_MAX_SPEED);
    stepper.setAcceleration(ULN2003_BASE_ACCELERATION);
    stepper.setSpeed(ULN2003_BASE_SPEED);
    lastTarget = 0;
}

void Uln2003Stepper::moveAbsolute(float targetDeg) {
    long targetSteps = (long)(targetDeg * angleToSteps);
    lastTarget = targetDeg;
    Logger::log(LOG_INFO, "Cap Picker moving to " + String(targetDeg, 2) + "° (" + String(targetSteps) + " steps)");
    stepper.moveTo(targetSteps);
    // Используем runToPosition() для блокирующего перемещения до цели
    stepper.runToPosition();
    Logger::log(LOG_INFO, "Cap Picker reached target");
}

void Uln2003Stepper::moveRelative(float deltaDeg) {
    float current = getAngle();
    float newTarget = current + deltaDeg;
    Logger::log(LOG_INFO, "Cap Picker relative move: current " + String(current, 2) +
                "°, delta " + String(deltaDeg, 2) + "°, new target " + String(newTarget, 2) + "°");
    moveAbsolute(newTarget);
}

float Uln2003Stepper::getAngle() {
    return stepper.currentPosition() / angleToSteps;
}

void Uln2003Stepper::setOrigin() {
    stepper.setCurrentPosition(0);
    lastTarget = 0;
    Logger::log(LOG_INFO, "Cap Picker origin set to 0°");
}

bool Uln2003Stepper::isMoving() {
    float current = getAngle();
    return fabs(current - lastTarget) > 0.5;
}

void Uln2003Stepper::stop() {
    stepper.stop();
    Logger::log(LOG_INFO, "Cap Picker stopped");
}

void Uln2003Stepper::release() {
    Logger::log(LOG_INFO, "Cap Picker released");
}

void Uln2003Stepper::lock() {
    Logger::log(LOG_INFO, "Cap Picker locked");
}

void Uln2003Stepper::setSpeed(float speedDegPerSec) {
    // Переводим скорость из градусов/с в шагов/с
    float speedStepsPerSec = speedDegPerSec * angleToSteps;
    stepper.setSpeed(speedStepsPerSec);
    Logger::log(LOG_INFO, "Uln2003Stepper speed set to " + String(speedDegPerSec) + "°/s");
}

void Uln2003Stepper::setAcceleration(float accelDegPerSec2) {
    // Переводим ускорение из градусов/с² в шаги/с²
    float accelStepsPerSec2 = accelDegPerSec2 * angleToSteps;
    stepper.setAcceleration(accelStepsPerSec2);
    Logger::log(LOG_INFO, "Uln2003Stepper acceleration set to " + String(accelDegPerSec2) + "°/s²");
}
