#include "timer.h"

Timer::Timer(unsigned long gapMillis, void (*callBackFunc)(void))
	: gapMillis(gapMillis), callBackFunc(callBackFunc){
	isTimerOn = 0;
}

void Timer::setTimerOn(){
	isTimerOn = 1;
	startMillis = millis();
}

void Timer::setTimerOff(){
	isTimerOn = 0;
}

void Timer::setGapTime(unsigned long timeMillis){
	gapMillis = timeMillis;
}

void Timer::setCallBackFunc(void (*callBackFunc)(void)){
	this->callBackFunc = callBackFunc;
}

void Timer::run(){
	if(!isTimerOn){
		return;
	}

	if((millis()-startMillis) > gapMillis){
		callBackFunc();
		startMillis = millis();
	}
}