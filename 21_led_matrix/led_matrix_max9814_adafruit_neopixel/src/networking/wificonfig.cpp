#include "wificonfig.h"

#include "util/properties.h"
#include <vector>

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "FS.h"

void
WiFiConfig::initialize() {
    std::vector<Property> properties;
    int propertiesRead = Properties::read("/access.properties", properties);

    initializeClientOnly(properties);
    // initializeClientAndServer(properties);
}

void 
WiFiConfig::initializeClientAndServer(const std::vector<Property>& properties) {
    Serial.println("initializing WiFi client...");
    
    String ssid = Properties::getValue("ssid", properties);
    String password = Properties::getValue("password", properties);

    Serial.print("connecting to : '");
    Serial.print(ssid);
    Serial.println("'");
    Serial.print("'");
    Serial.print(password);
    Serial.println("'");
    
    String serverSSID = Properties::getValue("serverssid", properties);
    String serverPassword = Properties::getValue("serverpassword", properties);
    
    WiFi.mode(WIFI_AP_STA);
    // TODO password
    WiFi.softAP(serverSSID.c_str());

    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void 
WiFiConfig::initializeClientOnly(const std::vector<Property>& properties) {

    Serial.println("initializing WiFi client...");

    String ssid = Properties::getValue("ssid", properties);
    String password = Properties::getValue("password", properties);

    Serial.print("connecting to : '");
    Serial.print(ssid);
    Serial.println("'");
    Serial.print("'");
    Serial.print(password);
    Serial.println("'");
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
