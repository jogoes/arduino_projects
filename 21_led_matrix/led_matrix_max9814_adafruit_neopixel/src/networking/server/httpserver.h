#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_

#include <vector>
#include "util/properties.h"

class ESP8266WebServer;

class WebServer {

private:
  ESP8266WebServer& m_server;

public:
  WebServer(ESP8266WebServer& server) : m_server(server) { }

public:
  void start(const std::vector<Property>& properties);

public:
  ESP8266WebServer& getServer() const { return m_server; }

private:
  void configureWebServer(const std::vector<Property>& properties);
};

#endif
