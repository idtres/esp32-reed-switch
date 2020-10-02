#ifndef timers_h
#define timers_h

#include "FS.h"
#include "time.h"

#define MAX_UINT32			0xFFFFFFFE

class timers{
    public:
    timers(uint64_t period);
    void restart();
    void restart(uint64_t period);
    void setPeriod(uint64_t period);
    uint64_t getPeriod();
    boolean check();
    boolean checkAndRestart();
    void forceExpire ();
    private:
    uint64_t startTimestamp;
    uint64_t restartPeriod;

};

#endif