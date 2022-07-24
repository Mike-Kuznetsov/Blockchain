#include <iostream>
#include "block.h"
#include "user.h"

using namespace std;

void User::start(int setDifficulty, int ID, User *setUser){
    myID=ID;
    user=setUser;
    block[0].createBlock(0,"0");
    block[0].addData("SYSTEM");
    block[0].hash=block[0].hashFunc();
    lastBlock=0;
    difficulty=setDifficulty;
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
}

bool User::checkBlock(Block *receivedBlock){
    //if ((*receivedBlock).prevHash==block[lastBlock].hash) cout << "Block checked" << endl;
    if (((*receivedBlock).prevHash==block[lastBlock].hash)
    && ((*receivedBlock).hashFunc().substr(0, difficulty)==zeros)
    && ((*receivedBlock).hashFunc()==(*receivedBlock).hash)){
        return true;
    }
    else{
        return false;
    }
}
void User::setBlock(Block receivedBlock){
    //cout << "USER " << myID << " received block" << endl;
    if (receivedBlock.number==block[lastBlock].number+1){
        if (checkBlock(&receivedBlock)){
            lastBlock++;
            block[lastBlock]=receivedBlock;
        }
    }
    else{
        cout << "USER " << myID << ": Block with incorrect number received" << endl;
        int maxBlock=lastBlock;
        int userID;
        for (int i=0; i<4; i++){
            if (user[i].lastBlock>maxBlock){
                maxBlock=user[i].lastBlock;
                userID=i;
            }
        }
        if (maxBlock>lastBlock){
            cout << "Max block in other user's blockchain: " << maxBlock << endl;
            cout << "Last block in this user's blockchain: " << lastBlock << endl;
            cout << "Downloading from user: " << userID << endl;
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
                for (int i=equalBlock+1; i<=lastBlock2; i++){
                    lastBlock++;
                    cout << "Downloading block: " << i << endl;
                    block[lastBlock]=user[userID].block[i];
                }
            }
            if (checkBlock(&receivedBlock) && (receivedBlock.number==block[lastBlock].number+1)){
                cout << "new received block added too" << endl;
                lastBlock++;
                block[lastBlock]=receivedBlock;
            }
        }
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
    for (int i=0; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].prevHash << endl;
        cout <<  block[i].hash << endl;
    }
}
void User::showData(){
    for (int i=0; i<=lastBlock; i++){
        cout << "Block: " << i << endl;
        cout <<  block[i].data << endl;
    }
}
