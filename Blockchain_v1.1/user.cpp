#include <iostream>
#include "block.h"
#include "user.h"

using namespace std;

void User::start(int setDifficulty){
    block[0].createBlock(0,"0");
    block[0].hash=block[0].hashFunc();
    lastBlock=0;
    difficulty=setDifficulty;
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
}
void User::setBlock(Block receivedBlock){
    if ((receivedBlock.hashFunc().substr(0, difficulty)==zeros) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
        lastBlock++;
        block[lastBlock]=receivedBlock;
    }
}
bool User::check(){
    for (int i=1; i<=lastBlock; i++){
        if (block[i].hash != block[i].hashFunc()){
            return false;
        }
        else if (block[i].prevHash != block[i-1].hashFunc()){
            return false;
        }
    }
    return true;
}
void User::showChain(){
    for (int i; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].prevHash << endl;
        cout <<  block[i].hash << endl;
    }
}
void User::showData(){
    for (int i; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].data << endl;
    }
}
