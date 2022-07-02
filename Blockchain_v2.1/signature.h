#ifndef SIGNATURE_H
#define SIGNATURE_H
class Signature {
    public:
        //std::string privKey;
        std::string pubKey;
        //unsigned char pubKey2;
        //unsigned char privKey2;
        unsigned char kekOutput[128];
        std::string keyGen();
        void encrypt(std::string privKey);
        void decrypt();
};

#endif
