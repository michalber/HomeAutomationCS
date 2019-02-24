#include <painlessMesh.h>
#include "PCSerial.h"

// some gpio pin that is connected to an LED...
// on my rig, this is 5, change to the right number of your LED.
#define INVERTED_OUT      0
#define LED               2       // GPIO number of connected LED, ON ESP-12 IS GPIO2
String  espID = "ESP01";

#define   BLINK_PERIOD    200 // milliseconds until cycle repeat
#define   BLINK_DURATION  100  // milliseconds LED is on for

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
// ----------------------------------------------------------------------------------------------------------------------------
// Prototypes
void sendMessage(); 
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback(); 
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay);

void uart_Update();
// ----------------------------------------------------------------------------------------------------------------------------
PCSerial PCCommunication;
// ----------------------------------------------------------------------------------------------------------------------------
Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
// ----------------------------------------------------------------------------------------------------------------------------
SimpleList<uint32_t> nodes;

void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval

void uartUpdate();
Task task_UART_Update(TASK_ONCE, TASK_FOREVER, &uartUpdate);
// ----------------------------------------------------------------------------------------------------------------------------
void setup() {
  //Serial.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, INVERTED_OUT);

  PCCommunication.Init(String("192.192.0.0"));
  
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  //mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION | COMMUNICATION);  // set before init() so that you can see startup messages
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();

  userScheduler.addTask( task_UART_Update );
  task_UART_Update.enable();
  
  randomSeed(analogRead(A0));
}
// ----------------------------------------------------------------------------------------------------------------------------
void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
//  digitalWrite(LED, !onFlag);
}
// ----------------------------------------------------------------------------------------------------------------------------
void uartUpdate() {
  PCCommunication.Update();
}
// ----------------------------------------------------------------------------------------------------------------------------
void sendMessage() {
  if(commandList.size() != 0) {
    String msg = commandList.pop();
    msg += "\r\n";
    mesh.sendBroadcast(msg);
     // ESP01GP20
    if(msg.substring(0,5) == espID){
      bool GPIOState = String(msg[8]).toInt();
      digitalWrite(LED,!GPIOState);
    }
    Serial.printf("Sending message: %s\n", msg.c_str());
  }
}
// ----------------------------------------------------------------------------------------------------------------------------
void receivedCallback(uint32_t from, String & msg) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}
// ----------------------------------------------------------------------------------------------------------------------------
void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task

  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
// ----------------------------------------------------------------------------------------------------------------------------
void changedConnectionCallback() {
  Serial.printf("Changed connections %s\n", mesh.subConnectionJson().c_str());
  // Reset blink task
 
  nodes = mesh.getNodeList();

  Serial.printf("Num nodes: %d\n", nodes.size());
  Serial.printf("Connection list:");

  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
}
// ----------------------------------------------------------------------------------------------------------------------------
void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
// ----------------------------------------------------------------------------------------------------------------------------
void delayReceivedCallback(uint32_t from, int32_t delay) {
  Serial.printf("Delay to node %u is %d us\n", from, delay);
}
