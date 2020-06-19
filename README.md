# ESP8266MqttMESH_ADHOC
A self-assembling ad-hoc mesh network using ESP8266.

## Overview

I have made a Self-assembling mesh network using ESP8266. 1 ESP8266 works as a root node (bridge) between the mqtt broker and other ESP8266s work as a node in the mesh. The mqtt broker receives messages from the root node and saves it in the text file. Any message from the root node can be broadcast to all nodes as well as send to a single node. The mqtt broker can send or receive messages by subscribing or publishing a topic respectively. 
The deepSleep mode is also available for nodes in the mesh network which reduces the power consumption in the mesh network. The nodes in the mesh start for 5 min. in every hour and after 5 min. it goes into deep sleep mode. Only the root node and the mqtt broker needs a continuous power supply.
 Here The mesh network is based on painlessMesh library. painlessMesh is a library that takes care of the particulars of creating a simple mesh network using esp8266 and esp32 hardware. painlessMesh is a true ad-hoc network, meaning that no-planning, central controller, or router is required. Any system of 1 or more nodes will self-organize into a fully functional mesh. For more information about painlessMesh library please visit [here](https://gitlab.com/painlessMesh/painlessMesh).

## Installations

### 1. Installations to program ESP8266 with Arduino IDE

1. Open up the Arduino IDE.
2. Go to File -> Preferences -> Additional Boards Manager URLs and paste this URL http://arduino.esp8266.com/stable/package_esp8266com_index.json -> click OK
3. Close the IDE and open it up again.
4. Go to Tools -> Board (where you’d select your version of Arduino) -> Boards Manager,type and search for the ESP8266 and click Install. You now should be able to use the ESP8266    as an Arduino. Simply select the "NODEMCU 1.0(ESP-12E MODULE)" as your board with Port and you should be ready to code.
Now, with ESP8266 board installed to Arduino IDE, we can program NodeMCU using Arduino IDE directly.

**1.   [painlessMesh](https://github.com/gmag11/painlessMesh)** 

**2. PubSubClient.h**  (Mqtt)
 <Open Arduino IDE, Go to Sketch -> Include Library -> Manage Libraries , Type and search for "**PubSubClient**" by **Nick O'Leary** and install it.>

 **3. [ArduinoJson](https://github.com/bblanchon/ArduinoJson)**

 **4. [TaskScheduler](https://github.com/arkhipenko/TaskScheduler)**

 **5. [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)**  (ESP8266)

 **6. [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)** (ESP32)


### 2.Python

#### 1. Install python from [here](https://www.python.org/downloads/).

#### 2. Install paho-mqtt
Now you have to install paho python client.This code provides a client class which enable applications to connect to an MQTT broker to publish messages, and to subscribe to topics and receive published messages. you can visit [here](https://pypi.org/project/paho-mqtt/) for installation instructions.


#### Setup :
1. Create a  **Wi-Fi  HOTSPOT** using your smartphone or router.
2. Now connect your PC with it using Wi-Fi.
3. Open **command prompt** and type  **ipconfig** and run to know your local ip address (This method is for **windows OS** PC. if you are not using windows operating system then search for methods to know your ip address.)
4. Now open the Arduino code and edit few lines of codes as per requirement.
5.  Now open python code and make few changes as per requirement.
6. Now upload the arduino code in ESP8266 Nodemcu via USB cable. And run the python code in your PC. A file with "**Filename**" will be generated in same folder where the python code is present. This file will contain the data send by nodes of mesh network.

**Note:** For deepsleep mode connect D0 pin with RST pin of ESP8266(nodes) after uploading the program. Remove connection between D0 and RST pin while uploading code otherwise code will not be uploaded.
![alt tag](https://user-images.githubusercontent.com/36708171/85125784-dee30c80-b249-11ea-9ec4-7c1daf3d03e8.png)
