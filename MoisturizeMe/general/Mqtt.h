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

char* tokenTopic(char* topic) {
  // this function will return the last token of a mqtt topic
  char* tmp;
  tmp = strtok (topic,"/");
  char* token = tmp;
  int length = 0;
  while (tmp != NULL)
  {
    length += 1;
    token = tmp;
    tmp = strtok (NULL, "/");
  }
  return token;
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
    

    // callback controller
    if(strstr(convertedTopic.c_str(),"controller/")) {
      debugI("Match moisturizers config");
      configController(tokenTopic(topic), content);
    }
    // callback moisturizers
    if(strstr(convertedTopic.c_str(),"moisturizers/")) {
      debugI("Match moisturizers config");
      configMoisturizer(tokenTopic(topic), content);
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
