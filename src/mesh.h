/*
Currently under development

Painless mesh header file created by modifying starter code from
https://gitlab.com/painlessMesh/painlessMesh/-/blob/develop/examples/startHere/startHere.ino?ref_type=heads
*/
#ifndef _MESH
#define _MESH
#include <arduino.h>
#include <painlessMesh.h>

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
#define BASE_STATION_ID 0

// setup() code for the mesh stored in a function, from starter code
void setupMesh(); 
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
