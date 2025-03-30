#pragma once
#include "HuffmanCoding.h"

class Application {
private:
    HuffmanCoding huffman;
    
    void compressFile();
    void decompressFile();
    void encryptFile();
    void decryptFile();
    void compressAndEncryptFile();
    void decryptAndDecompressFile();

public:
    void run();
};
