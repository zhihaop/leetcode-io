#ifndef LEETCODE_WRITER_H
#define LEETCODE_WRITER_H

#include <iostream>
#include "concepts.h"

class Writer {
    std::ostream &out;

    /**
     * write the value to buf.
     *
     * @param T         std::vector<?>.
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<typename T>
    requires detail::Vector<T>
    [[maybe_unused]] static void internal_write(std::string &buf, const T &value, const char *end_with = "\n") {
        buf += '[';
        for (int i = 0; i < value.size(); ++i) {
            if (i + 1 != value.size()) {
                internal_write(buf, value[i], ",");
            } else {
                internal_write(buf, value[i], "");
            }
        }
        buf += ']';
        buf += end_with;
    }

    /**
     * write the value to buf.
     *
     * @param T         int, float or double.
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<class T>
    requires detail::Number<T>
    [[maybe_unused]] static void internal_write(std::string &buf, const T &value, const char *end_with = "\n") {
        buf += std::to_string(value);
        buf += end_with;
    };

    /**
     * write the value to buf.
     *
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    [[maybe_unused]] static void internal_write(std::string &buf, const std::string &value, const char *end_with = "\n") {
        buf += '"';
        buf += value;
        buf += '"';
        buf += end_with;
    };

public:
    explicit Writer(std::ostream &out = std::cout) : out(out) {}

    /**
     * write the value to output stream.
     *
     * @tparam T        any type supported by the Writer.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<typename T>
    [[maybe_unused]] void write(const T &value, const char *end_with = "\n") {
        std::string buffer;
        internal_write(buffer, value, end_with);
        out << buffer;
    }
};

#endif //LEETCODE_WRITER_H
