#include <Arduino.h>
#include "FormelSIT.h"
#include "Debug.h"

FormelSIT::FormelSIT()
        : distances(), step(0), stepperDirection(true), longestDistanceIndex(0) {}

void FormelSIT::start() {
    lidar.begin();
    stepper.calibrate();
}

void FormelSIT::loop() {
    debugLog("");
    debugLog("------ NEXT LOOP CYCLE ------");
    // Change direction of servo if max/min position is reached
    if ((this->step+1) * 180.0f / MEASURE_POINTS >= 180) {
        stepperDirection = false;
    } else if ((this->step-1) <= 0) {
        stepperDirection = true;
    }

    //stepper.sweep();
    debugLog("Moving stepper " + ( stepperDirection ? String("right ") : String("left ") ) + String((STEPS_PER_REV) / (2 * MEASURE_POINTS)) + " steps");
    stepper.move((STEPS_PER_REV) / (2 * MEASURE_POINTS), stepperDirection);

    getDistance();

    calculateMoveDirection();

    this->step += stepperDirection ? 1 : -1;
}

void FormelSIT::calculateMoveDirection() {
    debugLog("Calculating move direction");
    if(distances[this->step] > distances[longestDistanceIndex]){
        longestDistanceIndex = this->step;
        debugLog("Found new longest distance, " + String(longestDistanceIndex));

        debugLog("Calling degree turn from FormelSIT");
        motor.degreeTurn(30, longestDistanceIndex*180 / ((float)MEASURE_POINTS-1));
#ifdef DEBUG_LIDAR
        for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
            if (i == longestDistanceIndex) {
                Serial.print("*");
            } else {
                Serial.print("-");
            }
        }
        Serial.println("   " + String(distances[longestDistanceIndex]));
#endif
    } else if (this->step == longestDistanceIndex) {
        debugLog("Did not find new distance, must check whole array");
        float newLongestDistance = 0;

        for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
            if (distances[i] > newLongestDistance) {
                newLongestDistance = distances[i];
                longestDistanceIndex = i;
            }
        }
    }
}

void FormelSIT::getDistance() {
    debugLog("Getting distance from lidar");
    distances[this->step] = lidar.getDistance();
}
