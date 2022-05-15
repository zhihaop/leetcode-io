#ifndef LEETCODE_WRITER_H
#define LEETCODE_WRITER_H

#include <iostream>
#include "concepts.h"

class Writer {
    std::ostream &out;

    template<typename T>
    requires detail::Vector<T>
    [[maybe_unused]] static void internal_write(std::string &buffer, const T &result, const char *end_with = "\n") {
        buffer += '[';
        for (int i = 0; i < result.size(); ++i) {
            if (i + 1 != result.size()) {
                internal_write(buffer, result[i], ",");
            } else {
                internal_write(buffer, result[i], "");
            }
        }
        buffer += ']';
        buffer += end_with;
    }

    template<class T>
    requires detail::Number<T>
    [[maybe_unused]] static void internal_write(std::string &buffer, const T &value, const char *end_with = "\n") {
        buffer += std::to_string(value);
        buffer += end_with;
    };

    [[maybe_unused]] static void
    internal_write(std::string &buffer, const std::string &value, const char *end_with = "\n") {
        buffer += '"';
        buffer += value;
        buffer += '"';
        buffer += end_with;
    };

public:
    explicit Writer(std::ostream &out = std::cout) : out(out) {}

    template<typename T>
    [[maybe_unused]] void write(const T &value, const char *end_with = "\n") {
        std::string buffer;
        internal_write(buffer, value, end_with);
        out << buffer;
    }
};

#endif //LEETCODE_WRITER_H
