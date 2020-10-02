#include <Arduino.h>
//#include <ArduinoJson.h>
#include "timers.h"
#include "config.h"
#include "myHelpers.h"
#ifdef ESP32

#endif

#include <WifiEspNow.h>
static uint8_t PEER[] {0xB6, 0xE6, 0x2D, 0x3C, 0x17, 0xC1};  

timers t_ledblink(2000);
timers t_readbuttons(10);

int contador = 0;

//#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex
#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 30 /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR bool updown = 0;
int pushButton = 12;
bool buttonState = LOW;

String payload;

void dosend(String datatosend) {
  char msg[64];
  //int len = snprintf(msg, sizeof(msg), "hello ESP-NOW from %s at %lu", payload.c_str(), millis());
  int len = snprintf(msg, sizeof(msg), datatosend.c_str(), millis());
  WifiEspNow.send(PEER, reinterpret_cast<const uint8_t*>(msg), len);
  Serial.println(datatosend);

}


void setup() {
  // Serial
  Serial.begin(115200);  Serial.println("");  Serial.println("Boot");

  setCpuFrequencyMhz(80);
  //WiFi.mode(WIFI_OFF);
  btStop();

  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Reed", nullptr, 3);
  WiFi.softAPdisconnect(false);

  bool ok = WifiEspNow.begin();
  if (!ok) {
    Serial.println("WifiEspNow.begin() failed");
    ESP.restart();
  }
  ok = WifiEspNow.addPeer(PEER);
  if (!ok) {
    Serial.println("WifiEspNow.addPeer() failed");
    ESP.restart();
  }


  pinMode(22,OUTPUT); digitalWrite(22,HIGH);

  myHelpers::ledInit(NEOPIXEL_PIN,NEOPIXEL_COUNT);
  myHelpers::ledClear();
  //myHelpers::ledbootsecuence();

  Serial.println(bootCount);
  bootCount = bootCount+1;
 
  buttonState = digitalRead(pushButton);
  updown = buttonState;
  Serial.println(buttonState);
  


  if (buttonState == HIGH) {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_12,0); //1 = High, 0 = Low
    Serial.println("me voy a dormir A");
    payload = (WiFi.softAPmacAddress());
    payload = payload + "/M/D/" + "1#" + String(analogRead(36) );
    
    for(int i = 0; i<5;i++){
      dosend(payload);
    }



    myHelpers::ledShow(1,0,255,0);
    myHelpers::ledShow(1,0,255,0);
    delay(3);
    myHelpers::ledShow(1,0,0,0);
    esp_deep_sleep_start();
  }
  
  Serial.println("me voy a dormir B");
  payload = (WiFi.softAPmacAddress());
  payload = payload + "/M/D/" + "0#" + String(analogRead(36) );

    for(int i = 0; i<5;i++){
      dosend(payload);
    }


  myHelpers::ledShow(1,255,0,0);
  myHelpers::ledShow(1,255,0,0);
  delay(3);
  myHelpers::ledShow(1,0,0,0);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_12,1); //1 = High, 0 = Low
  esp_deep_sleep_start();

  
}


void loop() {

  Serial.println(" nunca llegarias aca ");

}

