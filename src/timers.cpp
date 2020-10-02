#include "timers.h"

timers::timers(uint64_t period){
    this->startTimestamp = millis();
    this->restartPeriod = period;
}

void timers::setPeriod(uint64_t period){
    this->restartPeriod = period;
}
uint64_t timers::getPeriod(){
    return restartPeriod;
}

void timers::restart(){
    this->startTimestamp = millis();
}

void timers::restart(uint64_t period){
    this->startTimestamp = millis() + period;
}

void timers::forceExpire ()
{
    this->startTimestamp = 0;
}

boolean timers::check(){
    boolean result = false;
    if ( (millis() >= this->startTimestamp) ){
        if (millis() - this->startTimestamp >= this->restartPeriod) 
            result = true;
    }
    else
    {
         if (millis() + (MAX_UINT32 - this->startTimestamp ) >= this->restartPeriod) 
            result = true;
    }
    return result;
}

boolean timers::checkAndRestart(){
    boolean result = false;
    if (millis() >= this->startTimestamp ){
        if (millis() - this->startTimestamp >= this->restartPeriod )
        {
            this->startTimestamp = millis();
            result = true;
        }
    }
    else{
         if (millis() - (MAX_UINT32 - this->startTimestamp) >= this->restartPeriod )
        {
            this->startTimestamp = millis();
            result = true;
        }
    }
    return result;
}