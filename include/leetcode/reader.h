#ifndef LEETCODE_READER_H
#define LEETCODE_READER_H

#include <string>
#include <iostream>
#include "concepts.h"

class Reader {
    std::istream &in;

    /**
     * skip all the blank characters in the input stream.
     */
    inline void skip_blank() {
        int ch;
        for (;;) {
            ch = in.peek();
            if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
                in.get();
                continue;
            }
            return;
        }
    }

    /**
     * read value from the input stream.
     *
     * @tparam T        types that support std::iostream.
     * @param value     lvalue reference of the value.
     * @return          if read success, returns true.
     */
    template<class T>
    [[maybe_unused]] bool internal_read(T &value) {
        in >> value;
        return !in.fail();
    };

    /**
     * read a std::string from the input stream.
     *
     * @param input     lvalue reference of the string.
     * @return          if read success, returns true.
     */
    [[maybe_unused]] bool internal_read(std::string &input) {
        char ch;
        std::string result;

        in >> ch;
        if (ch != '"') {
            return false;
        }

        for (;;) {
            ch = static_cast<char>(in.get());
            if (ch == '\n' || ch == 0 || ch == -1) return false;
            if (ch == '"') break;
            result += ch;
        }

        input = std::move(result);
        return true;
    };

    /**
     * read a std::vector from the input stream.
     *
     * @tparam T        T is a std::vector.
     * @param input     lvalue reference of the vector.
     * @return          if read success, returns true.
     */
    template<typename T>
    requires detail::Vector<T>
    [[maybe_unused]] bool internal_read(T &input) {
        char ch;

        in >> ch;
        if (ch != '[') {
            return false;
        }

        T result{};
        for (;;) {
            skip_blank();

            // decide whether to read the next item.
            if (in.peek() == ']') {
                in.get();
                break;
            } else if (in.peek() == ',') {
                in.get();
            }

            typename T::value_type value{};
            if (!internal_read(value)) {
                return false;
            }

            result.emplace_back(std::move(value));
        }
        input = std::move(result);
        return true;
    }

    /**
    * read a std::map from the input stream.
    *
    * @tparam T        T is a std::map.
    * @param input     lvalue reference of the map.
    * @return          if read success, returns true.
    */
    template<typename T>
    requires detail::Map<T>
    [[maybe_unused]] bool internal_read(T &input) {
        char ch;

        in >> ch;
        if (ch != '{') {
            return false;
        }

        T result{};
        for (;;) {
            skip_blank();

            // decide whether to read the next item.
            if (in.peek() == '}') {
                in.get();
                break;
            } else if (in.peek() == ',') {
                in.get();
            }

            typename T::key_type key{};
            if (!internal_read(key)) {
                return false;
            }

            in >> ch;
            if (ch != ':') {
                return false;
            }

            typename T::value_type::second_type value{};
            if (!internal_read(value)) {
                return false;
            }
            result[key] = value;
        }
        input = std::move(result);
        return true;
    }

    /**
    * read a std::pair from the input stream.
    *
    * @tparam T        T is a std::pair.
    * @param input     lvalue reference of the map.
    * @return          if read success, returns true.
    */
    template<typename T>
    requires detail::Pair<T>
    [[maybe_unused]] bool internal_read(T &input) {
        char ch;

        in >> ch;
        if (ch != '(') {
            return false;
        }

        typename T::first_type key{};
        if (!internal_read(key)) {
            return false;
        }

        in >> ch;
        if (ch != ',') {
            return false;
        }

        typename T::second_type value{};
        if (!internal_read(value)) {
            return false;
        }

        in >> ch;
        if (ch != ')') {
            return false;
        }

        input = std::make_pair(std::move(key), std::move(value));
        return true;
    }

public:
    explicit Reader(std::istream &in = std::cin) : in(in) {}

    /**
     * read a value from input stream.
     *
     * @tparam T        any type supported by the Reader.
     * @param value     lvalue reference of the value.
     * @return          if read success, returns true.
     */
    template<typename T>
    [[maybe_unused]] bool read(T &value) {
        if (!internal_read(value)) {
            std::cerr << "format error: read(" + detail::name<T>() + ")" << std::endl;
            return false;
        }
        return true;
    };

};

#endif //LEETCODE_READER_H
