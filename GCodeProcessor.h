#ifndef GCODEPROCESSOR_H
#define GCODEPROCESSOR_H

#include <Arduino.h>
#include <GCodeParser.h>  // Предполагается наличие библиотеки GCodeParser
#include "StepperMotor.h"
#include "Uln2003Stepper.h"
#include "VibrMotor.h"
#include "OptoSensor.h"
#include "LEDController.h"
#include "Logger.h"
#include "AckModule.h"

class GCodeProcessor {
private:
    GCodeParser parser;
    StepperMotor* upperDisk;
    StepperMotor* lowerDisk;
    Uln2003Stepper* capPicker;
    VibrMotor* vibrMotor;
    OptoSensor* optoUpper;
    OptoSensor* optoLower;
    OptoSensor* optoCap;
    LEDController* ledController;
    bool absoluteMode;
	void setCurrentLine(String line);
public:
    GCodeProcessor(StepperMotor* u, StepperMotor* l, Uln2003Stepper* c,
                   VibrMotor* vm, OptoSensor* ou, OptoSensor* ol, OptoSensor* oc,
                   LEDController* led);
    void processLine(String line);
};

#endif // GCODEPROCESSOR_H
