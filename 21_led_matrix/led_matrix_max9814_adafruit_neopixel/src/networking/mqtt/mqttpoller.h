#ifndef _MQTT_POLLER_H_
#define _MQTT_POLLER_H_

#include "util/animated.h"

class MQTTPoller : public Animated {

private:
    MQTTClient& m_client;

public:
    MQTTPoller(MQTTClient& client, int delayMs) : Animated(delayMs), m_client(client) {
    }

    virtual void onShow() {
        m_client.loop();
    }
  
    virtual void onNext() {
    }
  
};

#endif