#ifndef LEETCODE_FORMATTER_DEBUGS_H
#define LEETCODE_FORMATTER_DEBUGS_H

#include "reader.h"
#include <sstream>
#include <string>

template<typename ...Args>
void from_string(const std::string &s, Args &...args) {
    std::stringstream ss(s);
    Reader reader(ss);
    reader.read(args...);
}

#endif //LEETCODE_FORMATTER_DEBUGS_H
