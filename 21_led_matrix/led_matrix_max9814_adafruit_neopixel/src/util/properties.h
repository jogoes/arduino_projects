#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include "WString.h"
#include <map>

class Properties {

private:
    std::map<String, String> m_properties;

public:
    void write(const String& path);
    void read(const String& path);
    const String& getValue(const String& name) const;
    const String& getValue(const char* name) const;
};

#endif