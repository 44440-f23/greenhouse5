/*
Currently under development

Painless mesh code created by modifying starter code from
https://gitlab.com/painlessMesh/painlessMesh/-/blob/develop/examples/startHere/startHere.ino?ref_type=heads
*/
#include <painlessMesh.h>
#include "mesh.h"
#include <ArduinoJson.h>

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;
Task taskSendMessage( TASK_SECOND * SEND_INTERVAL, TASK_FOREVER, &sendMessage ); // start with a one second interval
String mesh_msg;
int baseStationID = -1;
const size_t bufferSize = 1024; 

void setupMesh(){
  mesh.setDebugMsgTypes(ERROR | DEBUG);  // set before init() so that you can see error messages
  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void sendMessage() {
 if(baseStationID == -1)
  {
    Serial.println("BS has no id");
  }
  else
  {
    mesh.sendSingle(baseStationID, mesh_msg);
    Serial.printf("Sending message: %s\n", mesh_msg.c_str());
  }  
  mesh_msg = "";
}

uint32_t parseSimpleJson(const char* jsonString)
{
//create the parsable json object
StaticJsonDocument<bufferSize> jsonDoc;
DeserializationError error = deserializeJson(jsonDoc, jsonString);


// catch the errors if there are any
if (error) {
Serial.print("Failed to parse JSON: ");
Serial.println(error.c_str());
return 10;
}


uint32_t baseID = jsonDoc["basestation"];
return baseID;

}

