#ifndef CONFIG_H
#define CONFIG_H

// Пины для NEMA шаговых двигателей (верхний и нижний сортировочные диски)
#define STEPPER_UPPER_STEP_PIN  18
#define STEPPER_UPPER_DIR_PIN   19

#define STEPPER_UPPER_STEPS_PER_REVOLUTION 200

#define STEPPER_UPPER_REVERSE false
#define STEPPER_UPPER_SPEED_DEG_PER_SEC 360
#define STEPPER_UPPER_ACC_DEG_PER_SEC2 1000



#define STEPPER_LOWER_STEP_PIN  22
#define STEPPER_LOWER_DIR_PIN   23

#define STEPPER_LOWER_STEPS_PER_REVOLUTION 200

#define STEPPER_LOWER_REVERSE false
#define STEPPER_LOWER_SPEED_DEG_PER_SEC 360
#define STEPPER_LOWER_ACC_DEG_PER_SEC2 1000




// Константы для ULN2003 (механизм захвата крышечки)
#define ULN2003_IN1 2
#define ULN2003_IN2 4
#define ULN2003_IN3 16
#define ULN2003_IN4 17
#define ULN2003_STEPS_PER_REVOLUTION 4076   // Новая константа
#define ULN2003_MAX_SPEED 900
#define ULN2003_BASE_SPEED 200
#define ULN2003_BASE_ACCELERATION 100

// Пин для вибромотора
#define VIBR_PIN 14
#define VIBR_BASE_SPEED 255

// Пины для оптодатчиков и индивидуальные пороги срабатывания
#define OPTO_UPPER_PIN 27
#define OPTO_LOWER_PIN 33
#define OPTO_CAP_PIN   34

#define OPTO_UPPER_THRESHOLD 800
#define OPTO_LOWER_THRESHOLD 800
#define OPTO_CAP_THRESHOLD   800

// Параметры светодиодной ленты
#define LED_DATA_PIN 5
#define LED_NUM_LEDS 10
#define LED_TYPE WS2812B
#define LED_COLOR_ORDER GRB

#endif // CONFIG_H
