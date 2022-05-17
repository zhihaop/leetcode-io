#ifndef LEETCODE_CONCEPTS_H
#define LEETCODE_CONCEPTS_H

#include <map>
#include <vector>
#include <type_traits>

namespace detail {
    template<typename T>
    concept Map = std::is_same_v<T, std::map<typename T::key_type, typename T::value_type::second_type>>;

    template<typename T>
    concept Pair = std::is_same_v<T, std::pair<typename T::first_type, typename T::second_type>>;

    template<typename T>
    concept Vector = std::is_same_v<T, std::vector<typename T::value_type>>;

    template<typename T>
    [[maybe_unused]] inline std::string name() {
        return "unknown";
    }

    // forward declaration to resolve dependency issues
    template<class T> requires Map<T> inline std::string name();
    template<class T> requires Pair<T> inline std::string name();
    template<class T> requires Vector<T> inline std::string name();

    template<>
    [[maybe_unused]] inline std::string name<char>() {
        return "char";
    }

    template<>
    [[maybe_unused]] inline std::string name<int>() {
        return "int";
    }

    template<>
    [[maybe_unused]] inline std::string name<long>() {
        return "long";
    }

    template<>
    [[maybe_unused]] inline std::string name<long long>() {
        return "long long";
    }

    template<>
    [[maybe_unused]] inline std::string name<float>() {
        return "float";
    }

    template<>
    [[maybe_unused]] inline std::string name<double>() {
        return "double";
    }

    template<>
    [[maybe_unused]] inline std::string name<long double>() {
        return "long double";
    }

    template<class T>
    requires Map<T>
    [[maybe_unused]] inline std::string name() {
        return "std::map<" + detail::name<typename T::key_type>() + "," +  detail::name<typename T::value_type::second_type>() + ">";
    }

    template<class T>
    requires Pair<T>
    [[maybe_unused]] inline std::string name() {
        return "std::pair<" + detail::name<typename T::first_type>() + "," +  detail::name<typename T::second_type>() + ">";
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
