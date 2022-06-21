#include <iostream>
#include "sha256.h"
#include "block.h"
using namespace std;

void Block::setContent(int setNumber, string setPrevHash){
    prevHash=setPrevHash;
    number=setNumber;
    nonce=0;
    hash="";
    data="";
    //cout << "Block number: " << number << endl;
    //cout << "Previous Hash: " << prevHash << endl;
    //cout << endl;
    //cout << endl;
}

void Block::addData(string newData){
    data+=newData;
    //cout << "Data: " << data << endl;
}

string Block::hashFunc(){
    return sha256(to_string(number) + data + prevHash + to_string(nonce));
}
