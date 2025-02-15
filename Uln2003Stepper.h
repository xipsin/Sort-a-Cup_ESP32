#ifndef ULN2003STEPPER_H
#define ULN2003STEPPER_H

#include <Arduino.h>
#include <AccelStepper.h>
#include "Logger.h"
#include "Config.h"  // Для ULN2003_IN1, ULN2003_IN2 и т.д.

class Uln2003Stepper {
private:
    // Используем режим FULL4WIRE для управления драйвером ULN2003
    AccelStepper stepper;
    // Коэффициент перевода градусов в шаги (например, 4097 шагов = 1°)
    const float angleToSteps = ULN2003_STEPS_PER_REVOLUTION / 360.0;
    float lastTarget; // Последняя целевая позиция в градусах
public:
    Uln2003Stepper();
    void init();
    void moveAbsolute(float targetDeg);
    void moveRelative(float deltaDeg);
    float getAngle(); // Возвращает текущую позицию в градусах
    void setOrigin();
    bool isMoving();
    void stop();
    void release();
    void lock();
    // Новые методы для изменения скорости и ускорения (в градусах)
    void setSpeed(float speedDegPerSec);
    void setAcceleration(float accelDegPerSec2);
};

#endif // ULN2003STEPPER_H
