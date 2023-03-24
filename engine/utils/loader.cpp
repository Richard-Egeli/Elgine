#include "loader.hpp"

#include <fstream>
#include <ios>
#include <sstream>
#include <string>

std::string Loader::Shader(std::string path) {
    std::ifstream file(path);
    std::stringstream buffer;

    if (file.is_open()) buffer << file.rdbuf();

    return buffer.str();
}
