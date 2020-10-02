#ifndef jsonProcess_h
#define jsonProcess_h

#include "FS.h"
#include "ArduinoJson.h"

#define DEFAULT_JSON_SIZE 200

class jsonProcess{
    public:
    jsonProcess();
    static DeserializationError deserialize (String jsonStr, DynamicJsonDocument * jsonDoc);
    static bool serialize (DynamicJsonDocument jsonDoc, String * jsonStr);
    static bool addElement  (DynamicJsonDocument * jsonDoc, String field, String value);
    
    static String decodeText (String jsonRxStr, String jsonField, int indice);
    static double  decodeValue (String jsonRxStr, String jsonField, int indice);

};

#endif