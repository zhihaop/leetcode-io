#ifndef LEETCODE_CONCEPTS_H
#define LEETCODE_CONCEPTS_H

#include <map>
#include <vector>
#include <type_traits>
#include <unordered_map>

namespace detail {
    template<typename T>
    concept Map = std::is_same_v<T, std::map<typename T::key_type, typename T::value_type::second_type>>;

    template<typename T>
    concept UnorderedMap = std::is_same_v<T, std::unordered_map<typename T::key_type, typename T::value_type::second_type>>;

    template<typename T>
    concept Pair = std::is_same_v<T, std::pair<typename T::first_type, typename T::second_type>>;

    template<typename T>
    concept Array = std::is_same_v<T, std::array<typename T::value_type, std::tuple_size<T>::value>>;

    template<typename T>
    concept Tuple = !Pair<T> && !Array<T> && std::tuple_size<T>::value > 0;

    template<typename T>
    concept Vector = std::is_same_v<T, std::vector<typename T::value_type>>;

    template<typename T>
    concept Container = UnorderedMap<T> || Map<T> || Pair<T> || Array<T> || Tuple<T> || Vector<T>;

    template<typename T>
    [[maybe_unused]] inline std::string name() {
        return "unknown";
    }

    // forward declaration to resolve dependency issues
    template<class T>
    requires Map<T> inline std::string name();

    template<class T>
    requires Pair<T> inline std::string name();

    template<class T>
    requires Array<T> inline std::string name();

    template<class T>
    requires Tuple<T> inline std::string name();

    template<class T>
    requires Vector<T> inline std::string name();

    template<class T, size_t X>
    requires Tuple<T>
    [[maybe_unused]] inline std::string tuple_name();

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
        return "std::map<" + detail::name<typename T::key_type>() + "," +
               detail::name<typename T::value_type::second_type>() + ">";
    }

    template<class T>
    requires UnorderedMap<T>
    [[maybe_unused]] inline std::string name() {
        return "std::unordered_map<" + detail::name<typename T::key_type>() + "," +
               detail::name<typename T::value_type::second_type>() + ">";
    }

    template<class T>
    requires Pair<T>
    [[maybe_unused]] inline std::string name() {
        return "std::pair<" + detail::name<typename T::first_type>() + "," + detail::name<typename T::second_type>() +
               ">";
    }

    template<class T>
    requires Array<T>
    [[maybe_unused]] inline std::string name() {
        return "std::array<" + detail::name<typename T::value_type>() + "," +
               std::to_string(std::tuple_size<T>::value) + ">";
    }

    template<class T>
    requires Tuple<T>
    [[maybe_unused]] inline std::string name() {
        return detail::tuple_name<T, 0>();
    }

    template<class T, size_t X>
    requires Tuple<T>
    [[maybe_unused]] inline std::string tuple_name() {
        if constexpr(X == 0) {
            return "std::tuple<" +
                   detail::name<typename std::tuple_element_t<X, T>>() +
                   detail::tuple_name<T, X + 1>();
        } else if constexpr(X < std::tuple_size_v<T>) {
            return "," + detail::name<typename std::tuple_element_t<X, T>>() +
                   detail::tuple_name<T, X + 1>();
        } else {
            return ">";
        }
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
