#ifndef _TIMER_H_
#define _TIMER_H_

#include <Arduino.h>

class Timer{

private:
	bool isTimerOn;
	unsigned long startMillis;
	unsigned long gapMillis;
	void (*callBackFunc)(void);
public:
	Timer(unsigned long gapTime, void (*callBackFunc)(void));
	void setGapTime(unsigned long gapTime);
	void setCallBackFunc(void (*callBackFunc)(void));
	void setTimerOn();
	void setTimerOff();
	void run();
};

#endif