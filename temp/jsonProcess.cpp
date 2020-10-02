#include "jsonProcess.h"

DeserializationError jsonProcess::deserialize (String jsonStr, DynamicJsonDocument * jsonDoc){ // String a Json
    char jsonCh [DEFAULT_JSON_SIZE];
    jsonStr.toCharArray(jsonCh, jsonStr.length());
    DeserializationError error = deserializeJson(*jsonDoc, jsonCh);
    
    Serial.println("deserialize");
    serializeJsonPretty(*jsonDoc, Serial);

    Serial.println("deserializeAgain");
    serializeJsonPretty(*jsonDoc, Serial);
    
    return error;
}

bool jsonProcess::serialize  (DynamicJsonDocument jsonDoc, String * jsonStr){ // Json a String
    char jsonCh [DEFAULT_JSON_SIZE];
    if ( serializeJson(jsonDoc, jsonCh, DEFAULT_JSON_SIZE) ){
        * jsonStr = String(jsonCh);
        return false;
    }
    else
        return true;
}

bool jsonProcess::addElement  (DynamicJsonDocument * jsonDoc, String field, String value){
    DynamicJsonDocument jsonDocTemp (* jsonDoc);
    jsonDocTemp.getOrAddMember(field);
    jsonDocTemp[field] = value;

    *jsonDoc = jsonDocTemp ;

    return true;
}

String jsonProcess::decodeText (String jsonRxStr, String jsonField, int indice){ // lee texto
  StaticJsonDocument<200> RxDoc;
  DeserializationError error = deserializeJson(RxDoc, jsonRxStr);
  char jsonFieldChar[jsonField.length()];
  jsonField.toCharArray(jsonFieldChar, jsonField.length()+1);
  const char* jsonFieldOutChar = RxDoc[jsonFieldChar][indice];
  String jsonStringOutput(jsonFieldOutChar);
  return jsonStringOutput;
}

double  jsonProcess::decodeValue (String jsonRxStr, String jsonField, int indice){ // lee texto
  StaticJsonDocument<200> RxDoc;
  DeserializationError error = deserializeJson(RxDoc, jsonRxStr);
  char jsonFieldChar[jsonField.length()];
  jsonField.toCharArray(jsonFieldChar, jsonField.length()+1);
  double  jsonFieldOutLong = RxDoc[jsonFieldChar][indice];
  return jsonFieldOutLong;
}
