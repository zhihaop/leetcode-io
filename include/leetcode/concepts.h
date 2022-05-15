#ifndef LEETCODE_CONCEPTS_H
#define LEETCODE_CONCEPTS_H

#include <vector>
#include <type_traits>

namespace detail {
    template<typename T>
    concept Vector = std::is_same_v<T, std::vector<typename T::value_type>>;

    template<typename T>
    concept Number = std::is_arithmetic<T>::value;

    [[maybe_unused]] inline std::string name(char value) {
        return "char";
    }

    [[maybe_unused]] inline std::string name(int value) {
        return "int";
    }

    [[maybe_unused]] inline std::string name(float value) {
        return "float";
    }

    [[maybe_unused]] inline std::string name(double value) {
        return "double";
    }

    template<class T>
    requires Vector<T>
    [[maybe_unused]] inline std::string name(const T &value) {
        return "std::vector<T>";
    }

    [[maybe_unused]] inline std::string name(const std::string &value) {
        return "std::string";
    }
}

#endif //LEETCODE_CONCEPTS_H
