#include <iostream>
//#include "miner.h"
#include "user.h"
#include "block.h"
#include "signature.h"

using namespace std;

User::User(){
    Signature sig;
    privKey=sig.keyGen();
    pubKey=sig.pubKey;
}

void User::start(int ID, int setDifficulty, User *setUser, string *setPubKeys){
    difficulty=setDifficulty;
    pubKeys=setPubKeys;
    user=setUser;
    myID=ID;
    int balances[8];
    int transactionCount[8];
    for (int i=0;i<8;i++){
        balances[i]=0;
        transactionCount[i]=0;
    }
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
    block[0].createBlock(0, "", balances, transactionCount);
    block[0].hash=block[0].hashFunc();
    lastBlock=0;
}

bool User::checkTransactions(Block *receivedBlock){
    if ((*receivedBlock).transactions[0].value!=1 && (*receivedBlock).transactions[0].sender!="SYSTEM"){ // First Block check
        return false;
    }
    int receiverID;
    int senderID;
    for (int j=4; j<8; j++){ // Finding the ID of award receiver
        if ((*receivedBlock).transactions[0].receiver==pubKeys[j]){
            receiverID=j;
        }
    }
    balances[receiverID]++;
     for (int i=1; i<(*receivedBlock).lastTransaction; i++){
        for (int j=0; j<8; j++){ // Finding the ID of sender and receiver
            if ((*receivedBlock).transactions[i].sender==pubKeys[j]){
                senderID=j;
            }
            else if ((*receivedBlock).transactions[i].receiver==pubKeys[j]){
                receiverID=j;
            }
        }
        if ((!(*receivedBlock).transactions[i].check()) || ((*receivedBlock).transactions[i].value<=0) || (receiverID==senderID)){ // Transactions check
            return false;
        }
        balances[receiverID]=balances[receiverID]+(*receivedBlock).transactions[i].value; // Balances check
        balances[senderID]=balances[senderID]-(*receivedBlock).transactions[i].value;
    }
    for (int i=0; i<8; i++){
        if (balances[i]!=(*receivedBlock).balances[i]){
            return false;
        }
    }
    return true;
}

bool User::checkBlock(Block *receivedBlock){
    if (((*receivedBlock).prevHash==block[lastBlock].hash)
    && ((*receivedBlock).hash.substr(0, difficulty)==zeros)
    && ((*receivedBlock).hashFunc()==(*receivedBlock).hash)
    && (checkTransactions(receivedBlock))){
        return true;
    }
    else{
        return false;
    }
}

void User::setBlock(Block receivedBlock){ // Inserting block into blockchain after checking hashes and balances
    if (receivedBlock.number==block[lastBlock].number+1){
        for (int i=0; i<8; i++){
            balances[i]=block[lastBlock].balances[i];
        }
        //cout << "Transactions check: " << checkTransactions(&receivedBlock) << endl;
        if (checkBlock(&receivedBlock)){
            lastBlock++;
            block[lastBlock]=receivedBlock;
        }
    }
    else{
        cout << "USER " << myID+1 << ": Block with incorrect number received" << endl;
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
                for (int j=0; j<8; j++){
                    balances[j]=user[userID].block[i-1].balances[j];
                }
                if ((user[userID].block[i].prevHash==user[userID].block[i-1].hash)
                && (user[userID].block[i].hashFunc().substr(0, difficulty)==zeros)
                && (user[userID].block[i].hashFunc()==user[userID].block[i].hash)
                && (checkTransactions(&receivedBlock))){
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
