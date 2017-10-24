//
// Created by Viktor Hundahl Strate on 23/10/2017.
//

#ifndef LIDARROBOT_DEBUG_H
#define LIDARROBOT_DEBUG_H

#define DEBUG

#ifdef DEBUG
    #define debugLog(X) Serial.println(X)
#else
    #define debugLog(X)
#endif

#endif //LIDARROBOT_DEBUG_H