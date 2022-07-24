#include <iostream>
#include "miner.h"
#include "block.h"
#include "user.h"
#include <thread>

using namespace std;

void Miner::start(User *setUser, mutex *setMtx, int setDifficulty, Miner *setMiner, int ID){
    myID=ID;
    miner=setMiner;
    mtx=setMtx;
    user=setUser;
    block[0].createBlock(0,"0");
    block[0].addData("SYSTEM");
    block[0].hash=block[0].hashFunc();
    lastBlock=0;
    difficulty=setDifficulty;
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
    thread miner(mining, this);
    miner.detach();
}
bool Miner::checkBlock(Block *receivedBlock){
    if (((*receivedBlock).prevHash==block[lastBlock].hash)
    && ((*receivedBlock).hashFunc().substr(0, difficulty)==zeros)
    && ((*receivedBlock).hashFunc()==(*receivedBlock).hash)){
        return true;
    }
    else{
        return false;
    }
}
void Miner::setBlock(Block receivedBlock){
    if (receivedBlock.number==block[lastBlock].number+1){
        if (checkBlock(&receivedBlock)){
            blockAvailable=true;
            while(!minerStopped);
            lastBlock++;
            block[lastBlock]=receivedBlock;
            blockReceived=true;
        }
    }
    else{
        int maxBlock=lastBlock;
        int userID;
        for (int i=0; i<4; i++){
            if (user[i].lastBlock>maxBlock){
                maxBlock=user[i].lastBlock;
                userID=i;
            }
        }
        if (maxBlock>lastBlock){
            bool noErrors=true;
            int equalBlock=0;
            for (int i=lastBlock; i>0; i--){
                if (user[userID].block[i].hashFunc()==block[i].hash){
                    equalBlock=i;
                    break;
                }
            }
            int lastBlock2;
            for (int i=equalBlock+1; i<=maxBlock; i++){
                if ((user[userID].block[i].prevHash==user[userID].block[i-1].hash)
                && (user[userID].block[i].hashFunc().substr(0, difficulty)==zeros)
                && (user[userID].block[i].hashFunc()==user[userID].block[i].hash)){
                    lastBlock2=i;
                }
                else{
                    noErrors=false;
                    break;
                }
            }
            if (lastBlock2>lastBlock){
                blockAvailable=true;
                while(!minerStopped);
                for (int i=equalBlock+1; i<=lastBlock2; i++){
                    block[lastBlock]=user[userID].block[i];
                }
                if (checkBlock(&receivedBlock) && (receivedBlock.number==block[lastBlock].number+1)){
                    lastBlock++;
                    block[lastBlock]=receivedBlock;
                }
                blockReceived=true;
            }
        }
    }
}
void Miner::sendBlock(){
    for (int i=0; i<4; i++){
        if (((lastBlock+1==2) || (lastBlock+1==3) || (lastBlock+1==4)) && (i==1)){
            cout << "Block haven't been sended to user 1" << endl;
        }
        else{
            user[i].setBlock(block[lastBlock+1]);
        }
        if (myID!=i){
            miner[i].setBlock(block[lastBlock+1]);
        }
    }
}
void Miner::addData(string newData){
    (*mtx).lock();
    block[lastBlock+1].addData(newData);
    (*mtx).unlock();
}
void Miner::mining(){
    while(true){
        block[lastBlock+1].createBlock(block[lastBlock].number+1, block[lastBlock].hash);
        block[lastBlock+1].addData("Miner "+to_string(myID)+" - ");
        while (block[lastBlock+1].hashFunc().substr(0, difficulty)!=zeros){
            block[lastBlock+1].nonce++;
            if (blockAvailable){
                minerStopped=true;
                blockAvailable=false;
                while (!blockReceived);
                minerStopped=false;
                break;
            }
        }
        if (!blockReceived){
            (*mtx).lock();
            cout << "Block has been found by miner: " << myID << endl;
            block[lastBlock+1].hash=block[lastBlock+1].hashFunc();
            sendBlock();
            lastBlock++;
            (*mtx).unlock();
        }
        else{
            blockReceived=false;
        }
    }
}

bool Miner::check(){
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
void Miner::showChain(){
    for (int i=0; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].prevHash << endl;
        cout <<  block[i].hash << endl;
    }
}
void Miner::showData(){
    for (int i=0; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].data << endl;
    }
}

/*cout << "Block num: " << i << endl;
        cout << "Number: " << block[i].number << endl;
        cout << "prevHash: " << block[i].prevHash << endl;
        cout << "Data: " << block[i].data << endl;
        cout << "Nonce: " << block[i].nonce << endl;*/
