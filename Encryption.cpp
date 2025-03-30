#include "Encryption.h"
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>

std::string Encryption::encrypt(const std::string& data, const std::string& key) {
    std::string encrypted;
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), iv)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize AES encrypt context");
    }

    int outlen;
    encrypted.resize(data.length() + AES_BLOCK_SIZE);
    if (!EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&encrypted[0]), &outlen, reinterpret_cast<const unsigned char*>(data.c_str()), static_cast<int>(data.length()))) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to encrypt data");
    }

    int finaloutlen;
    if (!EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&encrypted[outlen]), &finaloutlen)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize AES encryption");
    }

    EVP_CIPHER_CTX_free(ctx);
    encrypted.resize(outlen + finaloutlen);
    return encrypted;
}

std::string Encryption::decrypt(const std::string& data, const std::string& key) {
    std::string decrypted;
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), iv)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize AES decrypt context");
    }

    int outlen;
    decrypted.resize(data.length());
    if (!EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&decrypted[0]), &outlen, reinterpret_cast<const unsigned char*>(data.c_str()), static_cast<int>(data.length()))) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to decrypt data");
    }

    int finaloutlen;
    if (!EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&decrypted[outlen]), &finaloutlen)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize AES decryption");
    }

    EVP_CIPHER_CTX_free(ctx);
    decrypted.resize(outlen + finaloutlen);
    return decrypted;
}
