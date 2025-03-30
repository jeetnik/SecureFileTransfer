#include "HuffmanCoding.h"
#include <queue>
#include <bitset>
#include <iostream>
#include <cstdint>  // Added for uint8_t and uint32_t

void HuffmanCoding::generateCodes(Node *root, std::string str) {
    if (!root) return;
    if (root->ch != '\0') huffmanCodes[root->ch] = str;
    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}

Node* HuffmanCoding::buildHuffmanTree(const std::string &text) {
    std::unordered_map<char, int> freq;
    for (char c : text) freq[c]++;
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto &pair : freq) pq.push(new Node(pair.first, pair.second));
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        pq.push(new Node('\0', left->freq + right->freq, left, right));
    }
    return pq.top();
}

std::string HuffmanCoding::bitsToString(const std::string &bits) {
    std::string result;
    for (size_t i = 0; i < bits.length(); i += 8)
        result += static_cast<char>(std::bitset<8>(bits.substr(i, 8)).to_ulong());
    return result;
}

std::string HuffmanCoding::stringToBits(const std::string &str) {
    std::string result;
    for (char c : str) result += std::bitset<8>(c).to_string();
    return result;
}

std::string HuffmanCoding::compress(const std::string &text) {
    if (text.empty()) {
        std::cerr << "Warning: Empty input text" << std::endl;
        return "";
    }
    Node *root = buildHuffmanTree(text);
    generateCodes(root, "");
    delete root;
    std::string compressed;
    for (char c : text) compressed += huffmanCodes[c];
    uint8_t paddingLength = 8 - (compressed.length() % 8);
    if (paddingLength < 8) compressed += std::string(paddingLength, '0');
    else paddingLength = 0;
    std::string result;
    result += static_cast<char>(paddingLength);
    result += static_cast<char>((text.length() >> 24) & 0xFF);
    result += static_cast<char>((text.length() >> 16) & 0xFF);
    result += static_cast<char>((text.length() >> 8) & 0xFF);
    result += static_cast<char>(text.length() & 0xFF);
    result += bitsToString(compressed);
    return result;
}

std::string HuffmanCoding::decompress(const std::string &compressed, const std::unordered_map<char, std::string> &codes) {
    if (compressed.length() < 5) {
        std::cerr << "Error: Compressed data is too short" << std::endl;
        return "";
    }
    uint8_t paddingLength = static_cast<uint8_t>(compressed[0]);
    uint32_t originalLength =
        (static_cast<unsigned char>(compressed[1]) << 24) |
        (static_cast<unsigned char>(compressed[2]) << 16) |
        (static_cast<unsigned char>(compressed[3]) << 8) |
        static_cast<unsigned char>(compressed[4]);
    std::string bits = stringToBits(compressed.substr(5));
    if (paddingLength > 0) bits = bits.substr(0, bits.length() - paddingLength);
    std::string decompressed;
    decompressed.reserve(originalLength);
    std::string currentCode;
    std::unordered_map<std::string, char> reverseMap;
    for (const auto &pair : codes) reverseMap[pair.second] = pair.first;
    for (char bit : bits) {
        currentCode += bit;
        if (reverseMap.find(currentCode) != reverseMap.end()) {
            decompressed += reverseMap[currentCode];
            currentCode.clear();
            if (decompressed.length() == originalLength) break;
        }
    }
    if (decompressed.length() != originalLength)
        std::cerr << "Warning: Decompressed length doesn't match original length" << std::endl;
    return decompressed;
}

std::unordered_map<char, std::string> HuffmanCoding::getCodes() const {
    return huffmanCodes;
}