#include "Stepper_Shan.h"

Stepper_Shan::Stepper_Shan(uint8_t enPin, uint8_t cwPin, uint8_t clkPin, uint8_t activeLow)
    : enPin(enPin), cwPin(cwPin), clkPin(clkPin), activeLow(activeLow) {
    pinMode(enPin, OUTPUT);
    pinMode(cwPin, OUTPUT);
    pinMode(clkPin, OUTPUT);
    digitalWrite(enPin, activeLow);
}

void Stepper_Shan::init(){
    digitalWrite(enPin, !activeLow);
}
    
void Stepper_Shan::takeOneStep(unsigned long perMicro){
    digitalWrite(clkPin, 1);
    delayMicroseconds(perMicro/2);
    digitalWrite(clkPin, 0);
    delayMicroseconds(perMicro/2);
}

void Stepper_Shan::takeOneStep(unsigned long perMicro, void (*restFunc)()){
    unsigned long delayTime;
    digitalWrite(clkPin, 1);
    delayTime = micros() + round(perMicro/2);
    while(micros() < delayTime){
        restFunc();
    }
    digitalWrite(clkPin, 0);
    delayTime = micros() + round(perMicro/2);
    while(micros() < delayTime){
        restFunc();
    }
}

void Stepper_Shan::stepsWithinMillis(long numSteps, unsigned long totalTimeMilli){
    digitalWrite(cwPin, numSteps>0);
    numSteps = abs(numSteps);
    unsigned long perMicro = (totalTimeMilli*1000)/numSteps;
    for(long i=0; i<numSteps; ++i){
        takeOneStep(perMicro);
    }
}

void Stepper_Shan::stepsWithinMillis(long numSteps, unsigned long totalTimeMilli, void (*restFunc)()){
    digitalWrite(cwPin, numSteps>0);
    numSteps = abs(numSteps);
    unsigned long perMicro = (totalTimeMilli*1000)/numSteps;
    for(long i=0; i<numSteps; ++i){
        takeOneStep(perMicro, restFunc);
    }
}

void Stepper_Shan::stepsPerMicro(long numSteps, unsigned long perMicro){
    digitalWrite(cwPin, numSteps>0);
    numSteps = abs(numSteps);
    for(long i=0; i<numSteps; ++i){
        takeOneStep(perMicro);
    }
}

void Stepper_Shan::stepsPerMicro(long numSteps, unsigned long perMicro, void (*restFunc)()){
    digitalWrite(cwPin, numSteps>0);
    numSteps = abs(numSteps);
    for(long i=0; i<numSteps; ++i){
        takeOneStep(perMicro, restFunc);
    }
}

void Stepper_Shan::stepsPerChangingMicro(long numSteps, unsigned long slowPerMicro, unsigned long fastPerMicro){
    digitalWrite(cwPin, numSteps>0);
    numSteps = abs(numSteps);
    long acceSteps = numSteps * 0.05;
    long nonAcceSteps = numSteps - (2*acceSteps);
    unsigned long timeMicro = slowPerMicro;
    for(long i=0; i<acceSteps; ++i){
        takeOneStep(timeMicro);
        timeMicro = map(i, 0, acceSteps-1, slowPerMicro, fastPerMicro);
    }
    for(long i=0; i<nonAcceSteps; ++i){
        takeOneStep(timeMicro);
    }
    for(long i=0; i<acceSteps; ++i){
        takeOneStep(timeMicro);
        timeMicro = map(i, 0, acceSteps-1, fastPerMicro, slowPerMicro);
    }
}
