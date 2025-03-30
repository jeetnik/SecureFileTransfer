#pragma once
#include <string>
#include <unordered_map>
#include "Node.h"

class HuffmanCoding {
private:
    std::unordered_map<char, std::string> huffmanCodes;

    void generateCodes(Node *root, std::string str);
    Node *buildHuffmanTree(const std::string &text);
    std::string bitsToString(const std::string &bits);
    std::string stringToBits(const std::string &str);

public:
    std::string compress(const std::string &text);
    std::string decompress(const std::string &compressed, const std::unordered_map<char, std::string> &codes);
    std::unordered_map<char, std::string> getCodes() const;
};