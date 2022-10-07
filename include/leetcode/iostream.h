#ifndef LEETCODE_IOSTREAM_H
#define LEETCODE_IOSTREAM_H

#include <iostream>
#include "leetcode/reader.h"
#include "leetcode/writer.h"

template<typename T>
requires detail::Container<T>
[[maybe_unused]] std::istream &operator>>(std::istream &is, T &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

template<typename T>
requires detail::Container<T>
[[maybe_unused]] std::ostream &operator<<(std::ostream &out, const T &value) {
    Writer writer(out);
    writer.write(value, "");
    return out;
}

[[maybe_unused]] std::istream &operator>>(std::istream &is, std::string &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

[[maybe_unused]] std::istream &operator>>(std::istream &is, char &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

[[maybe_unused]] std::istream &operator>>(std::istream &is, List &value) {
    Reader reader(is);
    reader.read(value);
    return is;
}

[[maybe_unused]] std::ostream &operator<<(std::ostream &out, const ListNode *node) {
    Writer writer(out);
    writer.write(node, "");
    return out;
}

[[maybe_unused]] std::ostream &operator<<(std::ostream &out, const List &l) {
    Writer writer(out);
    writer.write(l, "");
    return out;
}

#endif //LEETCODE_IOSTREAM_H
