#ifndef _MESH
#define _MESH
#include <arduino.h>
#include <painlessMesh.h>

#define   BLINK_PERIOD    3000 // milliseconds until cycle repeat
#define   BLINK_DURATION  100  // milliseconds LED is on for

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

#define TASK_SECOND 1

void sendMessage(); 
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback(); 
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay);

extern painlessMesh  mesh;
extern String mesh_msg;

// Sends message to base station. Assumes node dest_id is 0
void sendMessage();
#endif
