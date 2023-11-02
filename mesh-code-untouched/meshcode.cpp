#include <Arduino.h>
#include <painlessMesh.h>

#define LEDPIN 2

#define BLINK_PERIOD 3000
#define BLINK_DURATION 100

#define MESH_SSID "WhateverYouLike"
#define MESH_PASSWORD "SomethingSneaky"
#define MESH_PORT 5555

#define MESG_DELAY_SEC 2

const size_t bufferSize = 1024; 

uint32_t baseStationID = 0;

void receiveCallback(uint32_t from, String msg);
void newConnectionCallback(uint32_t nodeID);
void changedConnectionCallback();
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay); 
uint32_t parseSimpleJson(const char* jsonString);

void sendMessage();
Task taskSendMessage(TASK_SECOND * MESG_DELAY_SEC, TASK_FOREVER, &sendMessage);


Scheduler userSched;
painlessMesh mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;

Task blinkNoNodes;
bool onFlag = false;

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  mesh.setDebugMsgTypes(ERROR | DEBUG);
  // if(types & ERROR)

  mesh.init(MESH_SSID, MESH_PASSWORD, &userSched, MESH_PORT);
  mesh.onReceive(&receiveCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);

  userSched.addTask(taskSendMessage);
  taskSendMessage.enable();

  blinkNoNodes.set(BLINK_PERIOD, (mesh.getNodeList().size() + 1) * 2, []()
  {
    onFlag = !onFlag;
    blinkNoNodes.delay(BLINK_DURATION);
  });

  if(blinkNoNodes.isLastIteration())
  {
    blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
    blinkNoNodes.enableDelayed(BLINK_PERIOD - 
    (mesh.getNodeTime() % (BLINK_PERIOD * 1000)) / 1000);
  }

  userSched.addTask(blinkNoNodes);
  blinkNoNodes.enable();

  randomSeed(analogRead(A0));
}

void loop() {
  mesh.update();
  digitalWrite(LEDPIN, !onFlag);
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


  //Serial.printf("Sending message: %s\n", msg.c_str());
  Serial.println("Send: " + msg);
 
  //Scheduled every time between MSG_DELAY_SEC to 5 seconds
  taskSendMessage.setInterval( random(TASK_SECOND * MESG_DELAY_SEC, TASK_SECOND * 5));

  //String msg = "Luke is sending to base station";
  /*
  msg += mesh.getNodeId();
  msg += "Free memory: " + String(ESP.getFreeHeap());
  */
  //mesh.sendSingle(baseStationID, msg);
  /*
  if(calc_delay)
  {
    //SimpleList<uint32_t>::iterator
    auto node = nodes.begin();
    while(node != nodes.end())
    {
      mesh.startDelayMeas(*node);
      node ++;
    }
    calc_delay=false;
  }
  Serial.println("Sending msg: " + msg);
  taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SCHEDULE * 5));
  */
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


void newConnectionCallback(uint32_t nodeID)
{
  /*
  onFlag = false;
  blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
  blinkNoNodes.enableDelayed(BLINK_PERIOD - 
    (mesh.getNodeTime() % (BLINK_PERIOD * 1000)) / 1000);

   Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeID);
  Serial.printf("--> startHere: New Connection, %s\n", mesh.subConnectionJson(true).c_str());
*/
  
}

void changedConnectionCallback()
{
  /*
  Serial.printf("Changed connections\n");
  calc_delay = true;
  */

}


void nodeTimeAdjustedCallback(int32_t offset)
{
  /*
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
  */
}

void delayReceivedCallback(uint32_t from, int32_t delay)
{
  /*
  Serial.printf("Delay to node %u is %d us\n", from, delay);
  */
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
