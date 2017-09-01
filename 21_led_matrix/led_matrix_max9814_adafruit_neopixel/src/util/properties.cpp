#include "properties.h"

#include "util/fileutils.h"

#include "FS.h"

void
Properties::write(const String& path, std::vector<Property>& properties) {
    File f = SPIFFS.open(path, "w+");
    if(!f) {
        Serial.println("opening file '" + path + "' failed.");
        return;
    }
    String config = "";
    for(auto property = properties.begin(); property != properties.end(); property++) {
        if(property->getValue() == "") {
            config += property->getName();
        } else {
            config += property->getName() + "=" + property->getValue();
        }
        config += "\n";
    }

    f.write((const uint8_t*) config.c_str(), config.length());
    f.close();
}

int
Properties::read(const String& path, std::vector<Property>& properties) {
  File f = SPIFFS.open(path, "r");
  if(!f) {
    Serial.println("opening file '" + path + "' failed.");
    return 0;
  }

  // readString() somehow interfers with WiFi implementation
  // e.g. after calling readString() WiFi connections are not possible anymore
  //String propertiesStr = f.readString();
  String propertiesStr;
  while(f.available()) {
       propertiesStr += (char) f.read();
  }
  f.close();

  int current = 0;
  int next = 0;
  int count = 0;
  while(next >= 0) {
    next = propertiesStr.indexOf('\n', current);
    if(next >= 0) {
      String nameValue = propertiesStr.substring(current, next);
      int idx = nameValue.indexOf('=');
      if(idx >= 0) {
        String name = nameValue.substring(0, idx);
        name.trim();
        String value = nameValue.substring(idx + 1);
        value.trim();
        properties.push_back(Property(name, value));
        count++;
      } else {
        String name = nameValue.substring(0, idx);
        properties.push_back(Property(name, ""));
        count++;
      }
    }
    current = next + 1;
  }
  return count;
}

String
Properties::getValue(const String& name, const std::vector<Property>& properties) {
  String value = "";
  for(auto property = properties.begin(); property != properties.end(); property++) {
    if(property->getName() == name) {
      value = property->getValue();
    }
  }
  return value;
}

String
Properties::getValue(const char* name, const std::vector<Property>& properties) {
  return getValue(String(name), properties);
}