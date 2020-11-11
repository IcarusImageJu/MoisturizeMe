// MQTT Configuration
#include "MqttCredentials.h"
// const char* mqtt_server = "192.168.1.1";
// #define mqtt_port 1883
#define MQTT_CONTROLLERS_STATES_PUB "MoisturizeMe/controllers/states/0"
#define MQTT_CONTROLLERS_CONFIGS_SUB "MoisturizeMe/controllers/configs/0/#"
#define MQTT_VALUES_PUB "MoisturizeMe/values/0"
PubSubClient client(wifiClient);

void mqttReconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    debugI("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = HOST_NAME;
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_CONTROLLERS_STATES_PUB, 0, true, "{\"online\": false}")) {
      debugI("MQTT connected");
      //Once connected, publish an announcement...
      client.publish(MQTT_CONTROLLERS_STATES_PUB, "{\"online\": true}");
      // ... and resubscribe
      client.subscribe(MQTT_CONTROLLERS_CONFIGS_SUB);
    } else {
      debugW("failed, rc=", client.state());
      debugW("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte *payload, unsigned int length) {
    payload[length] = '\0';
    String convertedTopic = String(topic);
    String content = String((char*)payload);
  
    debugI("-------new message from broker-----");
    debugI("topic: %s", topic);
    debugI("payload: %d", payload);
    debugI("content: %s", content.c_str());
    debugI("length: %d", length);
    // callback for controller Id
    if(strcmp(topic, "MoisturizeMe/controllers/configs/0/controller/id") == 0) {
      debugI("Match id");
    }
    // callback for controller wifiSSid
    if(strcmp(topic, "MoisturizeMe/controllers/configs/0/controller/wifiSSid") == 0) {
      debugI("Match ssid");
    }
    // callback for controller wifiPass
    if(strcmp(topic, "MoisturizeMe/controllers/configs/0/controller/wifiPass") == 0) {
      debugI("Match pass");
    }
    // callback for controller mqttServer
    if(strcmp(topic, "MoisturizeMe/controllers/configs/0/controller/mqttServer") == 0) {
      debugI("Match mqtt");
    }
    // callback for controller name
    if(strcmp(topic, "MoisturizeMe/controllers/configs/0/controller/name") == 0) {
      debugI("Match name");
    }
    // callback moisturizers
    if(strstr(convertedTopic.c_str(),"moisturizers/")) {
      debugI("Match moisturizers config");
    }
}

void setupMqtt() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  mqttReconnect();
}

void loopMqtt() {
  client.loop();
}
