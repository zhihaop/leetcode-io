#ifndef LEETCODE_READER_H
#define LEETCODE_READER_H

#include <string>
#include <iostream>
#include "concepts.h"

class Reader {
    std::istream &in;

    template<class T>
    requires detail::Number<T>
    [[maybe_unused]] bool internal_read(T &value) {
        if (in) {
            in >> value;
            return !in.fail();
        }
        return false;
    };

    [[maybe_unused]] bool internal_read(std::string &input) {
        int ch;
        std::string result;

        do {
            ch = in.get();
        } while (in && (ch == ' ' || ch == '\n'));

        while (in) {
            ch = in.get();
            if (ch == '\n' || ch == 0 || ch == -1) return false;
            if (ch == '"') break;
            result += static_cast<char>(ch);
        }

        input = std::move(result);
        return true;
    };

    template<typename T>
    requires detail::Vector<T>
    [[maybe_unused]] bool internal_read(T &input) {
        int ch;
        do {
            ch = in.get();
        } while (in && (ch == ' ' || ch == '\n'));

        if (ch != '[')
            return false;

        T result{};
        for (;;) {
            typename T::value_type value{};
            if (internal_read(value)) {
                result.emplace_back(std::move(value));

                do {
                    ch = in.get();
                } while (in && (ch == ' ' || ch == '\n'));

                if (ch == ',') continue;
                if (ch == ']') break;
                return false;
            } else {
                return false;
            }
        }
        input = std::move(result);
        return true;
    }

public:
    explicit Reader(std::istream &in = std::cin) : in(in) {}

    template<typename T>
    [[maybe_unused]] bool read(T &value) {
        if (!internal_read(value)) {
            std::cerr << "format error: read(" + detail::name(value) + ")" << std::endl;
            return false;
        }
        return true;
    };

};

#endif //LEETCODE_READER_H
