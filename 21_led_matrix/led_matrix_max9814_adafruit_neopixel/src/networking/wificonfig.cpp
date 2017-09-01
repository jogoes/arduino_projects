#include "wificonfig.h"

#include "util/properties.h"

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "FS.h"

void
WiFiConfig::initialize(const Properties& properties) {
    initializeClientOnly(properties);
    // initializeClientAndServer(properties);
}

void 
WiFiConfig::initializeClientAndServer(const Properties& properties) {
    Serial.println("initializing WiFi client...");
    
    String ssid = properties.getValue("ssid");
    String password = properties.getValue("password");

    Serial.print("connecting to : '");
    Serial.print(ssid);
    Serial.println("'");
    Serial.print("'");
    Serial.print(password);
    Serial.println("'");
    
    String serverSSID = properties.getValue("serverssid");
    String serverPassword = properties.getValue("serverpassword");
    
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
WiFiConfig::initializeClientOnly(const Properties& properties) {

    Serial.println("initializing WiFi client...");

    String ssid = properties.getValue("ssid");
    String password = properties.getValue("password");

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
