#include<Arduino.h>

void setupMesh();
void receiveCallback(uint32_t from, String msg);
void sendMessage();
void updateMesh();
uint32_t parseSimpleJson(const char* jsonString);