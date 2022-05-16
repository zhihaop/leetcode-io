#ifndef LEETCODE_IOSTREAM_H
#define LEETCODE_IOSTREAM_H

#include <iostream>
#include "leetcode/reader.h"
#include "leetcode/writer.h"

template<typename T>
requires detail::Vector<T>
[[maybe_unused]] std::istream& operator >> (std::istream& is, T &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

template<typename T>
requires detail::Vector<T>
[[maybe_unused]] std::ostream& operator << (std::ostream& out, const T &value) {
    Writer writer(out);
    writer.write(value, "");
    return out;
}

[[maybe_unused]] std::istream& operator >> (std::istream& is, std::string &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

[[maybe_unused]] std::ostream& operator << (std::ostream& out, std::string &value) {
    Writer writer(out);
    writer.write(value, "");
    return out;
}
#endif //LEETCODE_FORMATTER_IOSTREAM_H
