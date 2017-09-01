#ifndef _WIFI_H_
#define _WIFI_H_

#include "util/properties.h"

#include <vector>

class WiFiConfig {
public:
    static void initialize();

private:
    static void initializeClientOnly(const std::vector<Property>& properties);
    static void initializeClientAndServer(const std::vector<Property>& properties);
};

#endif
