/*
 * Uses an LED matrix composed of WS2812 LEDs as display.
 *
 * This is the code for a version for which initially an Arduino was used.
 * To support connectivity the Arduino has been replaced by an ESP8266 NodeMCU board.
 *
 * Connections:
 *
 * D-SUB: numbered from left to right (RED wire=D-SUB1)
 *
 * Arduino   | RGBLED
 * --------------------
 * D6        | DIN
 * A0        | D-SUB3
 * A1        | D-SUB4
 * 5V        | D-SUB2
 * GND       | D-SUB1
 * GND       | GND
 * VIN       | 5V
 * 
 * Arduino   | MAX9814
 * ---------------------
 * 3,3V      | VCC
 * GND       | GND
 * Out       | A5
 */

#include <Arduino.h>

#include "util/color.h"

// work in progress
// #define USE_ADAFRUIT_NEOMATRIX

#ifdef USE_ADAFRUIT_NEOMATRIX
#include "display/display_adafruit_neomatrix.h"
#else
#include "display/display_fastled.h"
#endif

#include "font/font8x8.h"
#include "render/fontrenderer.h"
#include "render/textscroller.h"
#include "render/scrollingchart.h"

#include "sensor/max9814.h"

#include "util/fileutils.h"
#include "FS.h"

#include "networking/wificonfig.h"

// #include "networking/server/httpserver.h"
// #include "networking/controller/indexcontroller.h"

#include "networking/mqtt/mqttclient.h"
#include "networking/mqtt/mqttpoller.h"

#include "ESP8266WiFi.h"
// #include "ESP8266WebServer.h"

#include <ArduinoJson.h>

const int LED_DATA_PIN = 6;
const int AMPLIFIER_PIN = A0;

// Sample window width in milliseconds (50 mS = 20Hz)
const int SAMPLE_WINDOW_MS = 30;
// the maximum difference between minimum and maximum noise level
const int MAX_AMPLIFIER_VALUE = 510;

const int MIN_THRESHOLD = 30;

const int DISPLAY_WIDTH = 20;
const int DISPLAY_HEIGHT = 16;

Display* display;

FontRenderer* fontRenderer;

TextScroller* textScroller;
ScrollingChart* scrollingChart;

Max9814 max9814(AMPLIFIER_PIN);

#ifdef USE_ADAFRUIT_NEOMATRIX
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(DISPLAY_WIDTH, DISPLAY_HEIGHT, LED_DATA_PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);
#endif

/*
ESP8266WebServer espServer(80);
WebServer server(espServer);
IndexController indexController(server);

void handleIndex() {
  indexController.onIndex();
}

void configureHandlers() {
  ESP8266WebServer& espServer = server.getServer();

  espServer.on("/", handleIndex);
}
*/

String currentMessage;

WiFiClient wifiClient;
PubSubClient pubSubClient(wifiClient);
MQTTClient* mqttClient;
MQTTPoller* mqttPoller;

void
mqttCallback(const char* topic, byte* payload, unsigned int length) {
  MQTTClient::onMessageReceived(mqttClient, topic, payload, length);
}

void setupMQTT(const Properties& accessProperties) {
  String mqttClientName = accessProperties.getValue("mqtt.clientname");
  String mqttServer = accessProperties.getValue("mqtt.server");
  String mqttTopic = accessProperties.getValue("mqtt.topic");
  
  mqttClient = new MQTTClient(mqttClientName, pubSubClient, mqttServer, mqttTopic, mqttCallback);
  mqttPoller = new MQTTPoller(*mqttClient, 1000);
  mqttClient->connect();
}

void setup() {
  
  Serial.begin(9600);

  SPIFFS.begin();  
  FileUtils::ls("/");

  Properties accessProperties;
  accessProperties.read(String("/access.properties"));

  WiFiConfig::initialize(accessProperties);

  setupMQTT(accessProperties);
  
  //configureHandlers();
  //std::vector<Property> properties;
  //server.start(properties);

#ifdef USE_ADAFRUIT_NEOMATRIX
  matrix.begin();
  matrix.show();
  display = new Display_Adafruit_NeoMatrix(matrix);
#else
  display = new Display_FastLED<LED_DATA_PIN>(DISPLAY_HEIGHT, DISPLAY_WIDTH);
#endif

  scrollingChart = new ScrollingChart(*display, 10, MAX_AMPLIFIER_VALUE);
  fontRenderer = new FontRenderer(*display, Font8x8::get());
  textScroller = new TextScroller(*fontRenderer, currentMessage.c_str(), 0, 20, Color(0,0,255));
}

void loop() {
  if(mqttPoller->requiresUpdate()) {
    mqttPoller->next(false);
    const String& lastMessage = mqttClient->getLastMessage();
    if(textScroller != NULL && currentMessage != lastMessage) {
      currentMessage = lastMessage;
      textScroller->setMessage(lastMessage.c_str());
    }
  }


  int noiseLevel = max9814.sampleSignal(SAMPLE_WINDOW_MS);
  // cut off permanent noise
  int level = map(std::max(noiseLevel - MIN_THRESHOLD, 0), 0, MAX_AMPLIFIER_VALUE - MIN_THRESHOLD, 0, MAX_AMPLIFIER_VALUE);
  scrollingChart->setValue(level);

  //bool requiresUpdate = textScroller->requiresUpdate();
  bool requiresUpdate = true;
  if(requiresUpdate) {
    display->clear();
  }

  textScroller->next(requiresUpdate);
  scrollingChart->next(requiresUpdate);
  display->show();
}
