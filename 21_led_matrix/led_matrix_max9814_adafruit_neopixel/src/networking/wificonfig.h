#ifndef _WIFI_H_
#define _WIFI_H_

#include "util/properties.h"

class WiFiConfig {
public:
    static void initialize(const Properties& properties);

private:
    static void initializeClientOnly(const Properties& properties);
    static void initializeClientAndServer(const Properties& properties);
};

#endif
