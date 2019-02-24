#include <painlessMesh.h>

// some gpio pin that is connected to an LED...
// on my rig, this is 5, change to the right number of your LED.
#define INVERTED_OUT      1
#define   LED             2       // GPIO number of connected LED, ON ESP-12 IS GPIO2
String  espID = "ESP04";

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
// ----------------------------------------------------------------------------------------------------------------------------
Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
// ----------------------------------------------------------------------------------------------------------------------------
SimpleList<uint32_t> nodes;

void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
// ----------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, INVERTED_OUT);

  
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
  
  randomSeed(analogRead(A0));
}
// ----------------------------------------------------------------------------------------------------------------------------
void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
//  digitalWrite(LED, !onFlag);
}
// ----------------------------------------------------------------------------------------------------------------------------
void sendMessage() {
  String msg = "Hello from node ";
  msg += mesh.getNodeId();
  msg += " myFreeMemory: " + String(ESP.getFreeHeap());
  mesh.sendBroadcast(msg);

  Serial.printf("Sending message: %s\n", msg.c_str());
}
// ----------------------------------------------------------------------------------------------------------------------------

void receivedCallback(uint32_t from, String & msg) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  // ESP01GP20
  if(msg.substring(0,5) == espID){
    bool GPIOState = String(msg[8]).toInt();
    digitalWrite(LED,GPIOState);
  }
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
