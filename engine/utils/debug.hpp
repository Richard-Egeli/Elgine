#ifndef ENGINE_UTILS_DEBUG_HPP_
#define ENGINE_UTILS_DEBUG_HPP_

#include <iostream>
#include <string>

#define RED   "\033[1;31m"
#define NOR   "\033[0m"
#define GREEN "\033[1;32m"

class Debug {
 public:
    static void Log(const char* message);
    static void LogError(const char* message);
    static void LogSuccess(const char* message);

    template <typename T>
    static bool CheckNull(T* value, const std::string message) {
        bool result = value == nullptr;

        if (result) {
            std::cout << RED << message << NOR << std::endl;
        }

        return result;
    }
};

#endif  // ENGINE_UTILS_DEBUG_HPP_
