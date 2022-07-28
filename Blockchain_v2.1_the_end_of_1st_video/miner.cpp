#include <iostream>
#include "miner.h"
#include "user.h"
#include "block.h"
#include <thread>
#include "transaction.h"
#include "signature.h"
#include <mutex>
using namespace std;
const int difficulty = 5;

Miner::Miner(){
    Signature sig;
    privKey=sig.keyGen();
    pubKey=sig.pubKey;
}

void Miner::start(User *user1, Miner *miner1, int ID, mutex *setMtx, int setDifficulty, string *setPubKeys){
    pubKeys=setPubKeys;
    mtx=setMtx;
    user=user1;
    miner=miner1;
    myID=ID;
    difficulty=setDifficulty;
    int transactionCount[8];
    int balances[8];
    for (int i=0;i<8;i++){
        balances[i]=0;
        transactionCount[i]=0;
    }
    block[0].createBlock(0, "", balances, transactionCount);\
    block[0].hash=block[0].hashFunc();
    lastBlock=0;
    zeros="000000000000000000000000000000";
    zeros=zeros.substr(0, difficulty);
    thread thr(mining, this);
    thr.detach();
}

void Miner::sendBlock(){
    for (int i=0; i<4; i++){
        if (i!=myID){
            miner[i].setBlock(block[lastBlock+1]);
        }
        user[i].setBlock(block[lastBlock+1]);
    }
}

void Miner::addTransaction(Transaction *setTransaction){
    int newSenderID=0;
    int newReceiverID=0;
    for (int j=0; j<4; j++){ // Finding the ID of sender and receiver to check balances with these IDs
        if ((*setTransaction).sender==user[j].pubKey){
            newSenderID=j;
        }
        else if ((*setTransaction).receiver==user[j].pubKey){
            newReceiverID=j;
        }
        if ((*setTransaction).receiver==miner[j].pubKey){
            newReceiverID=j+4;
        }
        else if ((*setTransaction).sender==miner[j].pubKey){
            newSenderID=j+4;
        }
    }
    if(((*setTransaction).check()) && ((*setTransaction).value>0) && (newSenderID!=newReceiverID)) {
        if (block[lastBlock+1].balances[newSenderID]>=(*setTransaction).value){
            (*mtx).lock();
            block[lastBlock+1].addTransaction(*setTransaction);
            block[lastBlock+1].balances[newSenderID]=block[lastBlock+1].balances[newSenderID]-(*setTransaction).value;
            block[lastBlock+1].balances[newReceiverID]=block[lastBlock+1].balances[newReceiverID]+(*setTransaction).value;
            block[lastBlock+1].transactionCount[newSenderID]++;
            (*mtx).unlock();
            cout << "MINER " << myID+1 << ": Transaction was added to the block" << endl;
        }
        else{
            cout << "MINER " << myID+1 << ": You have not enough money" << endl;
        }
    }
    else{
        cout << "MINER " << myID+1 << ": Invalid transaction" << endl;
    }
}

bool Miner::checkTransactions(Block *receivedBlock){
    if ((*receivedBlock).transactions[0].value!=1 && (*receivedBlock).transactions[0].sender!="SYSTEM"){ // First Block check
        return false;
    }
    int receiverID;
    int senderID;
    for (int j=0; j<8; j++){ // Finding the ID of award receiver
        if ((*receivedBlock).transactions[0].receiver==pubKeys[j]){
            receiverID=j;
        }
    }
    balances[receiverID]++;
     for (int i=1; i<(*receivedBlock).lastTransaction; i++){
        if (!(*receivedBlock).transactions[i].check() || (*receivedBlock).transactions[i].value<=0){ // Transactions check
            return false;
        }
        for (int j=0; j<8; j++){ // Finding the ID of sender and receiver
            if ((*receivedBlock).transactions[i].sender==pubKeys[j]){
                senderID=j;
            }
            else if ((*receivedBlock).transactions[i].receiver==pubKeys[j]){
                receiverID=j;
            }
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

bool Miner::checkBlock(Block *receivedBlock){
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

void Miner::setBlock(Block receivedBlock){
    if (receivedBlock.number==block[lastBlock].number+1){
        for (int i=0; i<8; i++){
            balances[i]=block[lastBlock].balances[i];
        }
        if (checkBlock(&receivedBlock)){
            blockAvailable=true;
            while(!minerStopped);
            lastBlock++;
            block[lastBlock]=receivedBlock;
            blockReceived=true;
        }
    }
    else{
        cout << "Miner " << myID+1 << ": Block with incorrect number received" << endl;
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
                for (int j=0; j<8; j++){
                    balances[j]=user[userID].block[i-1].balances[j];
                }
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






void Miner::mining(){
    while(true){
        block[lastBlock+1].createBlock(block[lastBlock].number+1, block[lastBlock].hash, block[lastBlock].balances, block[lastBlock].transactionCount);
        block[lastBlock+1].balances[4+myID]++;
        Transaction transaction;
        string kek="SYSTEM";
        transaction.addData(0, kek, pubKey, 1);
        block[lastBlock+1].addTransaction(transaction);
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
            cout << "Block has been found by miner: " << myID+1 << endl;
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
