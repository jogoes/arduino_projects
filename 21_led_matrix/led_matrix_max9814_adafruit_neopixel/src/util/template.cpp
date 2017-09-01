#include "template.h"

#include "util/fileutils.h"

String 
Template::apply(const String& content, std::map<String, String> replacements) {
    String c(content);

    for(auto it = replacements.begin(); it != replacements.end(); it++) {
        auto key = it->first;
        auto value = it->second;
        c.replace("%" + key + "%", value);
    }
    return c;
}

String 
Template::getTemplate(const String& templateName) {
    return FileUtils::readFileByName(templateName);
}
