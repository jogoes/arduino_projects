#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "properties.h"

#include "WString.h"

class FileUtils {
public:
  static String readFile(const String& path);

  static String readFileByName(const String& name);

  static void ls(const String& path);
};

#endif