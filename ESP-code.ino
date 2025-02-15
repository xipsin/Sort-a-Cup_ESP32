#include <Arduino.h>
#include "Config.h"
#include "Logger.h"
#include "StepperMotor.h"
#include "Uln2003Stepper.h"
#include "VibrMotor.h"
#include "OptoSensor.h"
#include "LEDController.h"
#include "GCodeProcessor.h"

// Создаем объекты устройств
StepperMotor upperDisk(STEPPER_UPPER_STEP_PIN, STEPPER_UPPER_DIR_PIN, STEPPER_UPPER_STEPS_PER_REVOLUTION, 1);
StepperMotor lowerDisk(STEPPER_LOWER_STEP_PIN, STEPPER_LOWER_DIR_PIN, STEPPER_LOWER_STEPS_PER_REVOLUTION, 1);
Uln2003Stepper capPicker;
VibrMotor vibrMotor(VIBR_PIN);
OptoSensor optoUpper(OPTO_UPPER_PIN, OPTO_UPPER_THRESHOLD);
OptoSensor optoLower(OPTO_LOWER_PIN, OPTO_LOWER_THRESHOLD);
OptoSensor optoCap(OPTO_CAP_PIN, OPTO_CAP_THRESHOLD);
LEDController ledController;
GCodeProcessor gcodeProcessor(&upperDisk, &lowerDisk, &capPicker, &vibrMotor,
                              &optoUpper, &optoLower, &optoCap, &ledController);

void setup() {
    Serial.begin(115200);
    Logger::init();
    Logger::log(LOG_INFO, "System starting up...");
    
    // Инициализация устройств
    upperDisk.init();
	upperDisk.setSpeed(STEPPER_UPPER_SPEED_DEG_PER_SEC);
	upperDisk.setAcceleration(STEPPER_UPPER_ACC_DEG_PER_SEC2);
	
    lowerDisk.init();
	lowerDisk.setSpeed(STEPPER_LOWER_SPEED_DEG_PER_SEC);
	lowerDisk.setAcceleration(STEPPER_LOWER_ACC_DEG_PER_SEC2);
	
    capPicker.init();
    vibrMotor.init();
    optoUpper.init();
    optoLower.init();
    optoCap.init();
    ledController.init();
}

void loop() {
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        if (line.length() > 0) {
            gcodeProcessor.processLine(line);
        }
    }
}
