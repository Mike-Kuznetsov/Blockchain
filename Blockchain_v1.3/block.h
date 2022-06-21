#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Block {
    public:
    int number;
    std::string hash;
    std::string prevHash;
    std::string data;
    int nonce;
    void setContent(int setNumber, std::string setPrevHash);
    void addData(std::string newData);
    std::string hashFunc();
};

#endif
