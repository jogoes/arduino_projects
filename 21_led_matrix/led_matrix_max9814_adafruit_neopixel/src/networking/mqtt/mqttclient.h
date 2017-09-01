#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <PubSubClient.h>

class MQTTClient {
private:
    PubSubClient m_client;
    String m_name;
    String m_server;
    String m_topicName;
    int m_port;
    void (*m_callback)(const char*, byte*, unsigned int);

public:
    MQTTClient(const String& name, PubSubClient& client, const String& mqttServer, const String& topicName, void (*callback)(const char*, byte*, unsigned int)) : 
        m_name(name), 
        m_client(client), 
        m_server(mqttServer), 
        m_topicName(topicName),
        m_callback(callback),
        m_port(1883) {
        m_client.setServer(m_server.c_str(), m_port); 
        m_client.setCallback(m_callback);
    }

    bool connect() {
        if(m_client.connected()) {
            return true;
        }
        Serial.println("Connecting to " + m_server + "...");
        if(m_client.connect(m_name.c_str())) {
            m_client.subscribe(m_topicName.c_str());
            Serial.println("connected.");
            return true;
        } else {
            Serial.println("failed.");
            return false;
        }
    }

    void loop() {
        m_client.loop();
    }
};

#endif
