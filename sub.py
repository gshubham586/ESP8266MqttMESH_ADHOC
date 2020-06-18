# This program subscribe the message of nodes in the mesh network. The received message is saved in a text file with node id. The message starts with painless/from/12345678"
# where 12345678 is the node id of the node that has sent the message. The message includes the node name, Analog reading of pin A0 of ESP8266 and free memory present
# in ESP8266. Please enter the Local ip address of your PC/Laptop in the line with "****"
import paho.mqtt.client as mqtt
from datetime import datetime


 # The callback for when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))#Print result of connection attempt
    client.subscribe("painlessMesh/from/+")    # Subscribe all msg having topic "painlessMesh/from/"                       

filename= "filename.txt"

def on_message(client, userdata, msg):
    f = open(filename, "a")
    msg.payload = msg.payload.decode("utf-8")
    #Print a received msg
    print(datetime.now().strftime('%d/%m/%y %H:%M:%S:%f')[:-5] + " " + msg.topic + " " + str(msg.payload), file=f)  
    print(msg.topic + " " +datetime.now().strftime('%H:%M:%S:%f')[:-7] + " " + str(msg.payload))


client = mqtt.Client()  # Create instance of client with client ID “digi_mqtt_test”
client.on_connect = on_connect  # Define callback function for successful connection
client.on_message = on_message  # Define callback function for receipt of a message
client.connect("Enter ip address", 1883, 100)  #*****
client.loop_forever() 
