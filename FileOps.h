#pragma once
#include <string>

class FileOps {
public:
    static std::string readFile(const std::string &filename);
    static void writeFile(const std::string &filename, const std::string &data);
};