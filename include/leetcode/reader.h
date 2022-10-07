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
    requires (!detail::Container<T>)
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
        bool has_quote = true;
        if (ch != '"') {
            has_quote = false;
            result += ch;
        }

        for (;;) {
            ch = static_cast<char>(in.get());
            if (has_quote) {
                if (ch == '\n' || ch == 0 || ch == -1) return false;
                if (ch == '"') break;
            } else {
                if (ch == 0 || ch == -1) return false;
                if (ch == ' ' || ch == '\n') break;
            }
            result += ch;
        }

        input = std::move(result);
        return true;
    };

    /**
     * read a char from the input stream.
     *
     * @param input     lvalue reference of the string.
     * @return          if read success, returns true.
     */
    [[maybe_unused]] bool internal_read(char &input) {
        char ch, result;

        in >> ch;
        if (ch != '"') {
            return false;
        }

        in >> ch;
        if (ch == '\n' || ch == 0 || ch == -1) return false;
        result = ch;

        in >> ch;
        if (ch != '"') {
            return false;
        }

        input = result;
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
    requires detail::Map<T> || detail::UnorderedMap<T>
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
    * read a std::pair || std::array || std::tuple from the input stream.
    *
    * @tparam T        T is a std::pair || std::array || std::tuple.
    * @param input     lvalue reference of the map.
    * @return          if read success, returns true.
    */
    template<typename T, size_t X = 0>
    requires detail::Pair<T> || detail::Array<T> || detail::Tuple<T>
    [[maybe_unused]] bool internal_read(T &input) {
        char ch;
        if constexpr (X == 0) {
            in >> ch;
            if (ch != '(') {
                return false;
            }
        }

        if constexpr (X < std::tuple_size<T>::value) {
            if (!internal_read(std::get<X>(input))) {
                return false;
            }
        }

        in >> ch;
        if constexpr (X + 1 < std::tuple_size<T>::value) {
            if (ch != ',') {
                return false;
            }
            if (!internal_read<T, X + 1>(input)) {
                return false;
            }
        } else if (ch != ')') {
            return false;
        }
        return true;
    }

    /**
    * read a List from input.
    *
    * @param input     lvalue reference of the List.
    * @return          if read success, returns true.
    */
    [[maybe_unused]] bool internal_read(List &input) {
        std::vector<int> buffer;
        if (!internal_read(buffer)) {
            return false;
        }
        std::reverse(buffer.begin(), buffer.end());
        for (int &x: buffer) {
            input.emplace_front(x);
        }
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

    /**
     * read multiple values from input stream.
     *
     * @tparam T        any type supported by the Reader.
     * @tparam Args     the following params types.
     * @param value     lvalue reference of the value.
     * @param args      the following params.
     * @return          if read success, returns true.
     */
    template<typename T, typename ...Args>
    [[maybe_unused]] bool read(T &value, Args &...args) {
        if constexpr (sizeof...(args) > 0) {
            if (!read(value)) {
                return false;
            }
            return read(args...);
        }
        return read(value);
    };
};

#endif //LEETCODE_READER_H
