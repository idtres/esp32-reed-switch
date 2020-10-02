#if defined(ESP8266)
#include <ESP8266WiFi.h>
#define SD_CS D4 // wemos
#endif

#if defined ESP32
#define SDCARDREADER // si esta, hay SD
#include <WiFi.h>
#define SCK 14 // clock
#define MISO 2  // master out, slave in
#define MOSI 15 // 
#define SD_CS 13
#endif

#define BOARDNAME "DualBaseEsp" 
#define WIFI_CLIENT_DEFAULT_NETWORK "BrisaPirataBunker"
#define WIFI_CLIENT_DEFSULT_PASS "brisapirata1234"

#define UDP_PORT                41235
//#define STATUSLEDPIN 4  // esp32 cam gpio4=led
#define STATUSLEDPIN 2  //  wemos
#define STATUSLEDLOGIC // invierte la logica del led

//Salida NeoPixel
#define NEOPIXEL_PIN        27
#define NEOPIXEL_COUNT      3
#define DEFAULT_RED 0
#define DEFAULT_GREEN 32
#define DEFAULT_BLUE 0

//#define UPDATEPATH "http://10.0.0.10/hfs/"
#define UPDATEPATH "http://gprs.satelitech.com/totes/"
#define CODEVERSION 20200828
