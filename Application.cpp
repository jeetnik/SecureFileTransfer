#include "Application.h"
#include "Encryption.h"
#include "FileOps.h"
#include <iostream>
#include <stdexcept>
#include <openssl/evp.h>

void Application::compressFile() {
    std::string inputFile, outputFile;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    try {
        std::string content = FileOps::readFile(inputFile);
        std::string compressed = huffman.compress(content);
        FileOps::writeFile(outputFile, compressed);
        std::cout << "File compressed successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::decompressFile() {
    std::string inputFile, outputFile;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    try {
        std::string compressed = FileOps::readFile(inputFile);
        std::string decompressed = huffman.decompress(compressed, huffman.getCodes());
        FileOps::writeFile(outputFile, decompressed);
        std::cout << "File decompressed successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::encryptFile() {
    std::string inputFile, outputFile;
    std::string key;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    std::cout << "Enter encryption key (string): ";
    std::cin >> key;

    try {
        std::string content = FileOps::readFile(inputFile);
        std::string encrypted = Encryption::encrypt(content, key);
        FileOps::writeFile(outputFile, encrypted);
        std::cout << "File encrypted successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::decryptFile() {
    std::string inputFile, outputFile;
    std::string key;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    std::cout << "Enter decryption key (string): ";
    std::cin >> key;

    try {
        std::string encrypted = FileOps::readFile(inputFile);
        std::string decrypted = Encryption::decrypt(encrypted, key);
        FileOps::writeFile(outputFile, decrypted);
        std::cout << "File decrypted successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::compressAndEncryptFile() {
    std::string inputFile, outputFile;
    std::string key;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    std::cout << "Enter encryption key (string): ";
    std::cin >> key;

    try {
        std::string content = FileOps::readFile(inputFile);
        std::string compressed = huffman.compress(content);
        std::string encrypted = Encryption::encrypt(compressed, key);
        FileOps::writeFile(outputFile, encrypted);
        std::cout << "File compressed and encrypted successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::decryptAndDecompressFile() {
    std::string inputFile, outputFile;
    std::string key;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    std::cout << "Enter decryption key (string): ";
    std::cin >> key;

    try {
        std::string encrypted = FileOps::readFile(inputFile);
        std::string decrypted = Encryption::decrypt(encrypted, key);
        std::string decompressed = huffman.decompress(decrypted, huffman.getCodes());
        FileOps::writeFile(outputFile, decompressed);
        std::cout << "File decrypted and decompressed successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::run() {
    while (true) {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "  COMPRESSION & ENCRYPTION PROGRAM  \n";
        std::cout << "========================================\n";
        std::cout << "1. Compress a file\n";
        std::cout << "2. Decompress a file\n";
        std::cout << "3. Encrypt a file\n";
        std::cout << "4. Decrypt a file\n";
        std::cout << "5. Compress and encrypt a file\n";
        std::cout << "6. Decrypt and decompress a file\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: compressFile(); break;
            case 2: decompressFile(); break;
            case 3: encryptFile(); break;
            case 4: decryptFile(); break;
            case 5: compressAndEncryptFile(); break;
            case 6: decryptAndDecompressFile(); break;
            case 0: std::cout << "Exiting program.\n"; return;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
