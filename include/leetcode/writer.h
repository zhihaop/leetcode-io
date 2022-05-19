#ifndef LEETCODE_WRITER_H
#define LEETCODE_WRITER_H

#include <iostream>
#include "concepts.h"

class Writer {
    std::ostream &out;

    /**
     * write the value to the buf.
     *
     * @param T         std::map<?, ?>.
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<typename T>
    requires detail::Map<T>
    [[maybe_unused]] static void internal_write(std::string &buf, const T &value, const char *end_with = "\n") {
        buf += '{';
        size_t count = 0;
        for (auto it = value.begin(); it != value.end(); ++it, ++count) {
            internal_write(buf, it->first, "");
            buf += ':';
            internal_write(buf, it->second, "");
            if (count + 1 != value.size()) {
                buf += ',';
            }
        }
        buf += '}';
        buf += end_with;
    }

    /**
     * write the value to the buf.
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
     * write the value to the buf.
     *
     * @param T         std::pair || std::array || std::tuple.
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<typename T, size_t X = 0>
    requires detail::Pair<T> || detail::Tuple<T> || detail::Array<T>
    [[maybe_unused]] static void internal_write(std::string &buf, const T &value, const char *end_with = "\n") {
        if constexpr(X == 0) {
            buf += '(';
        }

        if constexpr(X < std::tuple_size<T>::value) {
            internal_write(buf, std::get<X>(value), "");
        }

        if constexpr(X + 1 < std::tuple_size<T>::value) {
            buf += ",";
            internal_write<T, X + 1>(buf, value, end_with);
        } else {
            buf += ')';
            buf += end_with;
        }
    }

    /**
     * write the value to the buf.
     *
     * @param T         types that support std::iostream.
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<class T>
    requires (!detail::Container<T>)
    [[maybe_unused]] static void internal_write(std::string &buf, const T &value, const char *end_with = "\n") {
        buf += std::to_string(value);
        buf += end_with;
    };

    /**
     * write the value to the buf.
     *
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    [[maybe_unused]] static void
    internal_write(std::string &buf, const std::string &value, const char *end_with = "\n") {
        buf += '"';
        buf += value;
        buf += '"';
        buf += end_with;
    };

    /**
     * write the value to the buf.
     *
     * @param buf       actually it is a std::string.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    [[maybe_unused]] static void
    internal_write(std::string &buf, const char &value, const char *end_with = "\n") {
        buf += '"';
        buf += value;
        buf += '"';
        buf += end_with;
    };

public:
    explicit Writer(std::ostream &out = std::cout) : out(out) {}

    /**
     * write the value to the output stream.
     *
     * @tparam T        any type supported by the Writer.
     * @param value     const lvalue reference of the value.
     * @param end_with  append `end_with` to the end of output.
     */
    template<typename T>
    [[maybe_unused]] void write(const T &value, const char *end_with = "\n") {
        std::string buffer;
        internal_write(buffer, value, end_with);
        out << buffer.data();
    }
};

#endif //LEETCODE_WRITER_H
