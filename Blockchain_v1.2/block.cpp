#include <iostream>
#include "sha256.h"

using namespace std;

class Block {
    public:
    int number;
    std::string hash;
    std::string prevHash;
    std::string data;
    int nonce;
    void setContent(int setNumber, string setPrevHash){
        prevHash=setPrevHash;
        number=setNumber;
        nonce=0;
        hash="";
        data="";
    }

    void addData(string newData){
        data+=newData;
    }

    string hashFunc(){
        return sha256(to_string(number) + data + prevHash + to_string(nonce));
    }
};
