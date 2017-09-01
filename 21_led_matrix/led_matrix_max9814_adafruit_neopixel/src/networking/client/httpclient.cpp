#include "httpclient.h"

#include <ESP8266WiFi.h>

void
HttpClient::get(const String& host, const String& url, HttpResponse& response) {
    WiFiClient client;
    if(!client.connect(host.c_str(), 80)) {
        Serial.println("Connection failed");
        return;
    }

    client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
        "Host: " + host + "\r\n" +
        "Connection: close\r\n\r\n"
    );
    delay(10);

    String reply;
    while(client.available()) {
        String line = client.readStringUntil('\r');
        reply += line;
    }

    response = HttpResponse(200, reply);
}