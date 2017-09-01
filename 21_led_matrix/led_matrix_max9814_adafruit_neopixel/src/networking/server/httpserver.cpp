#include "httpserver.h"

#include "util/properties.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

void
WebServer::configureWebServer(const Properties& properties) {
	Serial.println("Configuring access point...");
  // TODO get this from configuration
  const char *ssidESP = "ESPServer";
  const char *passwordESP = "simpleandeasy";

  WiFi.mode(WIFI_AP_STA);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssidESP/*, passwordESP*/);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  m_server.begin();
  Serial.println("HTTP server started");
}

void
WebServer::start(const Properties& properties) {
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    m_server.begin();
    Serial.println("HTTP server started");
    //configureWebServer(properties);
    //configureWiFiClient(properties);
}