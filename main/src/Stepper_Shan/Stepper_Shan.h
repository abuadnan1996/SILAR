#ifndef _STEPPER_SHAN_H_
#define _STEPPER_SHAN_H_
#include <Arduino.h>

class Stepper_Shan{

private:
    uint8_t initEn, enPin, cwPin, clkPin, activeLow;

public:
    Stepper_Shan(uint8_t enPin, uint8_t cwPin, uint8_t clkPin, uint8_t activeLow = 1);
    void init();
    void takeOneStep(unsigned long perMicro);
    void takeOneStep(unsigned long perMicro, void (*restFunc)());
    void stepsWithinMillis(long numSteps, unsigned long totalTimeMilli);
    void stepsWithinMillis(long numSteps, unsigned long totalTimeMilli, void (*restFunc)());
    void stepsPerMicro(long numSteps, unsigned long perMicro);
    void stepsPerMicro(long numSteps, unsigned long perMicro, void (*restFunc)());
    void stepsPerChangingMicro(long numSteps, unsigned long perMicro, unsigned long finalPerMicro);
};

#endif
