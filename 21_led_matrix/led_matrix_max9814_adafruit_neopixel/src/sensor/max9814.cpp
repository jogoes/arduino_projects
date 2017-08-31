#include "max9814.h"

#include <Arduino.h>

unsigned int 
Max9814::sampleSignal(int sampleWindowMs) {
    unsigned long startMs = millis();
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    while(millis() - startMs < sampleWindowMs) {
        unsigned int sample = analogRead(m_pin);
        if(sample < 1024) { // eliminate spikes
            signalMax = max(signalMax, sample);
            signalMin = min(signalMin, sample);
        }
    }

    return signalMax - signalMin;
}
