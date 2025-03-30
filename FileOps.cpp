#include "FileOps.h"
#include <fstream>
#include <stdexcept>
#include <openssl/evp.h>
#include <openssl/aes.h>


std::string FileOps::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening input file: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void FileOps::writeFile(const std::string &filename, const std::string &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening output file: " + filename);
    }
    file.write(data.c_str(), data.length());
}