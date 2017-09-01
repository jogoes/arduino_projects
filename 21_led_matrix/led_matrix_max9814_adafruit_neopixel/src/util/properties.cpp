#include "properties.h"

#include "util/fileutils.h"

#include "FS.h"

const String EMPTY_STR;

void
Properties::write(const String& path) {
    File f = SPIFFS.open(path, "w+");
    if(!f) {
        Serial.println("opening file '" + path + "' failed.");
        return;
    }
    String config = "";
    for(auto property = m_properties.begin(); property != m_properties.end(); property++) {
        auto name = property->first;
        auto value = property->second;
        if(value == "") {
            config += name;
        } else {
            config += name + "=" + value;
        }
        config += "\n";
    }

    f.write((const uint8_t*) config.c_str(), config.length());
    f.close();
}

void 
Properties::read(const String &path) {
    m_properties.clear();
    File f = SPIFFS.open(path, "r");
    if(!f) {
      Serial.println("opening file '" + path + "' failed.");
      return;
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
          m_properties.insert(std::pair<String, String>(name, value));
        } else {
          String name = nameValue.substring(0, idx);
          m_properties.insert(std::pair<String, String>(name, ""));
        }
      }
      current = next + 1;
    }
}

const String&
Properties::getValue(const char* name) const {
    return getValue(String(name));
}

const String&
Properties::getValue(const String& name) const {
    auto it = m_properties.find(name);
    if(it == m_properties.end()) {
        return EMPTY_STR;
    }
    return it->second;
}
