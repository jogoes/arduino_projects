#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <Arduino.h>

#include <map>

class Template {

public:
  static String apply(const String& content, const std::map<String, String>& replacements);

  static String getTemplate(const String& templateName);
};

#endif