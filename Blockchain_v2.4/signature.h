#ifndef SIGNATURE_H
#define SIGNATURE_H
class Signature {
    public:
        std::string pubKey;
        unsigned char kekOutput[128];
        std::string keyGen();
        std::string encrypt(std::string input, std::string *privKey);
        unsigned char* decrypt(std::string *input, std::string *pubKey2);
};

#endif
