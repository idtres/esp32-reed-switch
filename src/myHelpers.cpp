#include "myHelpers.h"
#include <Wire.h>

#include <FastLED.h>
#include "config.h"


CRGBArray<NEOPIXEL_COUNT> leds;

void myHelpers::ScanForI2C(int SDAPIN, int SCLPIN){
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  Wire.begin(SDAPIN,SCLPIN); //   Wire.begin(SDA,SCL);
  //Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);          // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);     // PCF8574 7 bit address
      Serial.print (") ");
      count++;
    }
  }
  Serial.print (" Found ");      
  Serial.print (count, DEC);        // numbers of devices
  Serial.println (" device(s).");
}

void myHelpers::ledInit(int ledPin, int ledAmount)
{
  FastLED.addLeds<NEOPIXEL,NEOPIXEL_PIN>(leds, NEOPIXEL_COUNT);
}

void myHelpers::ledShow(int index, int r, int g, int b)
{
   leds[index] = CRGB(r,g,b);
   FastLED.show();
}

void myHelpers::ledbuffer(int index, int r, int g, int b)
{
   leds[index] = CRGB(r,g,b);
}

void myHelpers::ledRender()
{
  FastLED.show();
}


void myHelpers::ledShow(int index, bool state, int r, int g, int b)
{
  if(state){
   leds[index] = CRGB(r,g,b);
   FastLED.show();
   }
   if(!state){
   leds[index] = CRGB(DEFAULT_RED,DEFAULT_GREEN,DEFAULT_BLUE);
   FastLED.show();
   }
}

void myHelpers::ledClear()
{
  FastLED.clear();
}

void myHelpers::ledbootsecuence(){
    for(int i = 0; i<4;i++){
    myHelpers::ledShow(0,255,255,255);
    delay(100);
    myHelpers::ledShow(0,0,8,0);
    delay(100);
  }
}


int myHelpers::HexToDec(String hexString) {
  unsigned int decValue = 0;
  int nextInt;
  for (int i = 0; i < hexString.length(); i++) {
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    decValue = (decValue * 16) + nextInt;
  }
  return decValue;
}


String myHelpers::DecToHex(int valuetoconvert){
  char temp_string[10];
  sprintf(temp_string, "%04X", valuetoconvert);
  return String(temp_string);
}

#ifdef defined(ESP32)



void myHelpers::GoToSleepFor(int segundos){
  uint64_t sleepcount = segundos * 1000000;
  Serial.println("Me fui a dormir por: "+ String(segundos));
  esp_sleep_enable_timer_wakeup(sleepcount);
  esp_deep_sleep_start();
}

void myHelpers::LowPower(){
  setCpuFrequencyMhz(80);
  WiFi.mode(WIFI_OFF);
  btStop();
}

int myHelpers::WakeUpReason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  return wakeup_reason;
}

void myHelpers::PrintWakeUpReason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
    switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("[" + String(wakeup_reason) + "] Desperte por PIN externo, si no hay alarma en el ACCEL fue el ReedSwitch"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("[" + String(wakeup_reason) + "] Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("[" + String(wakeup_reason) + "] akeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("[" + String(wakeup_reason) + "] Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("[" + String(wakeup_reason) + "] Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

#endif