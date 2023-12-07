#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "MQTTClient.h"
#include "GPIO.h"
#include "GPIO.cpp"
using namespace std;
using namespace exploringBB;



#define ADDRESS    "tcp://io.adafruit.com"
#define CLIENTID   "Beagle1"
#define TOPIC      "cv1123/feeds/projtemp.button-status"
#define AUTHMETHOD "cv1123"
#define AUTHTOKEN  "aio_gOGH08LI7Bd1Jqg3xHGcvxqgOaHi"
#define QOS        1
#define TIMEOUT    10000L
#define GPIO_PIN   46 
#define GPIO_PATH "/sys/class/gpio/"

int main(int argc, char* argv[]) {
	GPIO inGPIO(46);
	inGPIO.setDirection(INPUT);
   
	 inGPIO.getValue();

    
	printf("\n Value of pin = %d", inGPIO.getValue() );
	printf("\n Status of pin = %d\n", inGPIO.getDirection() );
   
   
   char str_payload[100];          // Set your max message size here
   MQTTClient client;
   cout << "Starting Beagle board MQTT Adafruit Publish Example" << endl;
   MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
   MQTTClient_message pubmsg = MQTTClient_message_initializer;
   MQTTClient_deliveryToken token;
   MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
   opts.keepAliveInterval = 20;
   opts.cleansession = 1;
   opts.username = AUTHMETHOD;
   opts.password = AUTHTOKEN;
   int rc;
   if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
      cout << "Failed to connect, return code " << rc << endl;
      return -1;
   }
   sprintf(str_payload, "%d", inGPIO.getValue());   // <--------- this is where value gets sent
   pubmsg.payload = str_payload;
   pubmsg.payloadlen = strlen(str_payload);
   pubmsg.qos = QOS;
   pubmsg.retained = 0;
   MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
   cout << "Waiting for up to " << (int)(TIMEOUT/1000) <<
        " seconds for publication of " << str_payload <<
        " \non topic " << TOPIC << " for ClientID: " << CLIENTID << endl;
   rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
   if(rc == MQTTCLIENT_SUCCESS) {
     cout << "Message with token " << (int)token << " delivered." << endl;
   }
   else {
     cout << "Did not complete with error code: " << rc << endl;   
     MQTTCLIENT_MAX_MESSAGES_INFLIGHT -4
     MQTTCLIENT_NULL_PARAMETER -6
     MQTTCLIENT_BAD_STRUCTURE -8
     MQTTCLIENT_SSL_NOT_SUPPORTED   -10;
   }
   MQTTClient_disconnect(client, 10000);
   MQTTClient_destroy(&client);
   return rc;
}