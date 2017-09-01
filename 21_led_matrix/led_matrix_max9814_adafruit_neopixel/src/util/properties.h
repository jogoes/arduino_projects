#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include "WString.h"
#include <vector>

class Property {
private:
  String m_name;
  String m_value;

public:
  Property(const String& name, const String& value) : m_name(name), m_value(value) {
  }
  Property(const Property& prop) {
    m_name = prop.m_name;
    m_value = prop.m_value;
  }

public:
  const String& getName() const { return m_name; }
  const String& getValue() const { return m_value; }
};

class Properties {
public:
  static void write(const String& path, std::vector<Property>& properties);

  static int read(const String& path, std::vector<Property>& properties);

  static String getValue(const String& name, const std::vector<Property>& properties);
  static String getValue(const char* name, const std::vector<Property>& properties);
};

#endif