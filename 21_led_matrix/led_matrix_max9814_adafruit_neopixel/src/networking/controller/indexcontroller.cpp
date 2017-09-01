#include "indexcontroller.h"

#include "util/fileutils.h"
#include "util/networkutils.h"
#include "util/template.h"

#include <WString.h>
#include <map>

#include <Arduino.h>

void
IndexController::onIndex() {
    Serial.println("onIndex");
    String indexTemplate = FileUtils::readFile("/index.html");
    std::map<String, String> model;
    model["CONTENT"] = "";
    String response = Template::apply(indexTemplate, model);
    ok(response);
}

void IndexController::onScan() {
    int networksFound = NetworkUtils::scanNetwork();
    String response = String(networksFound) + " networks found";
    ok(response);
}