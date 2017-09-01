
#include "basecontroller.h"
#include "util/fileutils.h"

#include "networking/server/httpserver.h"

#include "ESP8266WebServer.h"

void
Controller::ok(const String& response)
{
  m_server.getServer().send(200, "text/html", response);
}

String
Controller::readIndex() {
  return FileUtils::readFile("/index.html");
}