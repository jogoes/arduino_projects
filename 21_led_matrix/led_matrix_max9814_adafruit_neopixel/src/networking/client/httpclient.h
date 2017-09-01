#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include "util/properties.h"

#include <Arduino.h>

class HttpResponse {
private:
    int m_statusCode;
    String m_content;

public:
    HttpResponse(int statusCode, const String& content) : m_statusCode(statusCode), m_content(content) {

    }

public:
    int statusCode() { return m_statusCode; };
    const String& content() { return m_content; }
};

class HttpClient {

public:
    void get(const String& host, const String& url, HttpResponse& response);
};

#endif
