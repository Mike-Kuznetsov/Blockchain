#include <iostream>
#include "miner.h"
#include "block.h"
#include "user.h"
#include <thread>

using namespace std;

void Miner::start(User *setUser, mutex *setMtx, int setDifficulty){
    mtx=setMtx;
    user=setUser;
    currentBlock.createBlock(0,"0");
    currentBlock.hash=currentBlock.hashFunc();
    currentBlock.createBlock(1,currentBlock.hash);
    difficulty=setDifficulty;
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
    thread miner(mining, this);
    miner.detach();
}
void Miner::sendBlock(){
    for (int i=0; i<4; i++){
        user[i].setBlock(currentBlock);
    }
    currentBlock.createBlock(currentBlock.number+1, currentBlock.hash);
}
void Miner::addData(string newData){
    (*mtx).lock();
    currentBlock.addData(newData);
    (*mtx).unlock();
}
void Miner::mining(){
    while(true){
        while (currentBlock.hashFunc().substr(0, difficulty)!=zeros){
            currentBlock.nonce++;
        }
        //cout << "Block has been found" << endl;
        //cout << "HASH: " << currentBlock.hash << endl;
        (*mtx).lock();
        currentBlock.hash=currentBlock.hashFunc();
        sendBlock();
        (*mtx).unlock();
    }
}
