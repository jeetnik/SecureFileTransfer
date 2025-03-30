#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    /**
     * Encrypts the given data using AES with the provided key.
     *
     * @param data The data to be encrypted.
     * @param key The encryption key.
     * @return The encrypted data.
     */
    static std::string encrypt(const std::string& data, const std::string& key);

    /**
     * Decrypts the given data using AES with the provided key.
     *
     * @param data The data to be decrypted.
     * @param key The decryption key.
     * @return The decrypted data.
     */
    static std::string decrypt(const std::string& data, const std::string& key);
};

#endif // ENCRYPTION_H
