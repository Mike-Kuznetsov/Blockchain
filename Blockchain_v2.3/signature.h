#ifndef SIGNATURE_H
#define SIGNATURE_H
class Signature {
    public:
        std::string pubKey;
        unsigned char kekOutput[128];
        std::string keyGen();
        unsigned char* encrypt(std::string input, std::string *privKey);
        void decrypt();
};

#endif
