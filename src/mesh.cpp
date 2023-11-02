#include <Arduino.h>
#include <painlessMesh.h>
#include <mesh.h>


#define MESH_SSID "WhateverYouLike"
#define MESH_PASSWORD "SomethingSneaky"
#define MESH_PORT 5555
#define MESG_DELAY_SEC 2
const size_t bufferSize = 1024; 
uint32_t baseStationID = 0;


Scheduler userSched;
painlessMesh mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;

Task taskSendMessage(TASK_SECOND * MESG_DELAY_SEC, TASK_FOREVER, &sendMessage);


void setupMesh()
{
    mesh.setDebugMsgTypes(ERROR | DEBUG);
    mesh.init(MESH_SSID, MESH_PASSWORD, &userSched, MESH_PORT);
    mesh.onReceive(&receiveCallback);
    userSched.addTask(taskSendMessage);
    taskSendMessage.enable();
    randomSeed(analogRead(A0));
}


void receiveCallback(uint32_t from, String msg)
{
  Serial.printf("Received: from %u msg=%s\n", from, msg.c_str());
  try
  {
    baseStationID = parseSimpleJson(msg.c_str());
  }
  catch(const std::exception& e)
  {
    Serial.printf("ERROR in json parse");
  }

  
}

void sendMessage()
{
   String msg = "Greenhouse 5\n\n";


  if(baseStationID == 0)
  {
    Serial.println("BS has no id");
  }
  else
  {
    mesh.sendSingle(baseStationID, msg);
  }

    Serial.println("Send: " + msg);
    taskSendMessage.setInterval( random(TASK_SECOND * MESG_DELAY_SEC, TASK_SECOND * 5));
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

void updateMesh()
{
    mesh.update();
}