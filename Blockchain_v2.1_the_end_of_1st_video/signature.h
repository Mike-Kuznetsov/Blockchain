#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string>

class Signature {
    public:
        std::string pubKey;
        std::string keyGen();
        std::string encrypt(std::string input, std::string *privKey);
        std::string decrypt(std::string *input, std::string *pubKey2);
};

#endif
