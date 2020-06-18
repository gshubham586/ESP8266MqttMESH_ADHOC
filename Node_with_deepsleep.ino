//************************************************************
// This is an exmample for the nodes in the mesh network. Write root node id in the line 32.
// For deepsleep mode connect D0 pin with RST pin of ESP8266(nodes) after uploading the code.
// Remove connection between D0 and RST pin while uploading code otherwise code will not be uploaded.
//************************************************************

#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"                         // Mesh Prefix (SSID) should be same for all  nodes in Mesh Network
#define   MESH_PASSWORD   "somethingSneaky"                         // Mesh Password should be same for all  nodes in Mesh Network
#define   MESH_PORT       5555                                      // Mesh Port should be same for all  nodes in Mesh Network

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

unsigned long period=0;  

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain


Task taskSendMessage( TASK_SECOND * 4 , TASK_FOREVER, &sendMessage );   // Set task second to send msg in a time interval (Here interval is 4 second)


// If you want to receive sensor readings from this node, write code in below function....

void sendMessage() {
  String msg = "NODE no./name  ";                                       // You can write node name/no. here so that you may easily recognize it        
  msg += mesh.getNodeId();                                              // Adding Node id in the msg
  msg+= " Analog: " + String (analogRead(A0));                          // Adding  analog reading in the msg. You can also add other pin readings 
  msg += " myFreeMemory: " + String(ESP.getFreeHeap());                 // Adding free memory of Nodemcu in the msg
  uint32_t target = 2768191281;                                         // Target is Node id of the node where you want to send sms (Here, write node id of mqtt bridge (Root Node))
  mesh.sendSingle(target, msg );                                        // Send msg to single node. To broadcast msg (mesh.sendBroadcast(msg))
  Serial.println(msg);
 //Serial.println("WiFi signal: " + String(WiFi.RSSI()) + " db");       // Prints wi-fi signal strength in db
}


// Msg recived by node. If you want to perform any task by receiving msg, write code in the below function....

void receivedCallback( uint32_t from, String &msg ) {
 Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
if (msg=="LightON")
 {
  digitalWrite(LED_BUILTIN, LOW);                                       // If msg published from mqtt broker is LightON, Turn ON the built in LED of Nodemcu
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    }
}

void newConnectionCallback(uint32_t nodeId) {
   Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
 Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
   Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | DEBUG );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  //mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.setContainsRoot(true);
  
  
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
  pinMode(A0, INPUT);                                                    // Define A0 pin as INPUT
  pinMode(LED_BUILTIN, OUTPUT);                                          // Define LED_BUILTIN as OUTPUT
  digitalWrite(LED_BUILTIN, HIGH);                                       // Initially the LED will be off
  
  
}

void loop() {
  // it will run the user scheduler as well

period=millis()/1000;                                                    // Function "mllis()" gives time in milliseconds. Here "period" will store time in seconds
 
  mesh.update();

           //digitalWrite(LED_BUILTIN,LOW);                              // LED will be ON when node in not deepSleep mode                               
  
  if (period>60)                                                         // When period will be > 60 seconds, deep sleep mode will be active
  {
     mesh.stop();
 ESP.deepSleep(300e6);                                                    // deepSleep mode will be active for 300*10^6 microseconds, i.e. for 300 seconds                                                   
 digitalWrite(LED_BUILTIN,HIGH); 
  }
}
void delayReceivedCallback(uint32_t from, int32_t delay) {
  Serial.printf("Delay to node %u is %d us\n", from, delay);
}
