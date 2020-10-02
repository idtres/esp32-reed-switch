#ifndef myHelpers_h
#define myHelpers_h

#include "Arduino.h"




class myHelpers{
    public:
    static void ScanForI2C(int SDA, int SCL);
    static void ledInit(int ledPin, int ledAmount);
    static void ledShow(int index, int r, int g, int b);
    static void ledbuffer(int index, int r, int g, int b);
    static void ledShow(int index, bool state, int r, int g, int b );
    static void ledRender();
    static void ledbootsecuence();
    static void ledClear();
    static void SetSleepTime(int segundos);
    static void GoToSleepNow();
    static void GoToSleepFor(int segundos);
    static int WakeUpReason();
    static void PrintWakeUpReason();
    static int SmartSleep();
    static int HexToDec(String hex);
    static String DecToHex(int dec);
    static void LowPower();
};

#endif

