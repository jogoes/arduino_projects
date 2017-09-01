#ifndef _BASE_CONTROLLER_H_
#define _BASE_CONTROLLER_H_

class WebServer;
class String;

class Controller {

protected:
  WebServer& m_server;

public:
  Controller(WebServer& server) : m_server(server) { }

public:
  void ok(const String& response);

  String readIndex();
  String readFile(const String& path);
  String readFileByName(const String& name);
};

#endif