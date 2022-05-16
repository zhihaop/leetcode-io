#ifndef LEETCODE_CONCEPTS_H
#define LEETCODE_CONCEPTS_H

#include <vector>
#include <type_traits>

namespace detail {
    template<typename T>
    concept Vector = std::is_same_v<T, std::vector<typename T::value_type>>;

    template<typename T>
    concept Number = std::is_arithmetic<T>::value;

    template<typename T>
    [[maybe_unused]] inline std::string name() {
        return "unknown";
    }

    template<>
    [[maybe_unused]] inline std::string name<char>() {
        return "char";
    }

    template<>
    [[maybe_unused]] inline std::string name<int>() {
        return "int";
    }

    template<>
    [[maybe_unused]] inline std::string name<float>() {
        return "float";
    }

    template<>
    [[maybe_unused]] inline std::string name<double>() {
        return "double";
    }

    template<class T>
    requires Vector<T>
    [[maybe_unused]] inline std::string name() {
        return "std::vector<" + detail::name<typename T::value_type>() + ">";
    }

    template<>
    [[maybe_unused]] inline std::string name<std::string>() {
        return "std::string";
    }
}

#endif //LEETCODE_CONCEPTS_H
