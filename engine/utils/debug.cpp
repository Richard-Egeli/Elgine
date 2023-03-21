#include "debug.hpp"

#include <iostream>

void Debug::Log(const char* message) { std::cout << message << std::endl; }

void Debug::LogError(const char* message) {
    std::cout << "\033[1;31m"
              << "ERROR: " << message << "\033[0m" << std::endl;
}

void Debug::LogSuccess(const char* message) {
    std::cout << "\033[1;32m"
              << "SUCCESS: " << message << "\033[0m" << std::endl;
}
