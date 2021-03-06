#include "Stepper.h"


Stepper::Stepper() {
    pinMode(STEPPER_DIRECTION, OUTPUT);
    pinMode(STEPPER_STEP, OUTPUT);
    pinMode(HALL_SENSOR, INPUT_PULLUP);

    digitalWrite(STEPPER_DIRECTION, LOW);
    digitalWrite(STEPPER_STEP, LOW);
}

void Stepper::calibrate() {
    while (digitalRead(HALL_SENSOR) == HIGH)
        move(1, false);

    move(50-26, false);
}

void Stepper::move(uint8_t steps, boolean dir) {
    digitalWrite(STEPPER_DIRECTION, dir ? HIGH : LOW);
    for (int i = steps; i > 0; i--) {
        digitalWrite(STEPPER_STEP, HIGH);
        delay(STEPPER_WAIT_TIME);
        digitalWrite(STEPPER_STEP, LOW);
        delay(STEPPER_WAIT_TIME);
    }
}

void Stepper::sweep() {
    move(100, true);
    move(100, false);
}
