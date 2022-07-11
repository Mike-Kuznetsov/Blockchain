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

void Miner::start(User *user1, Miner *miner1, int ID, mutex *setMtx){
    mtx=setMtx;
    user=user1;
    miner=miner1;
    minerID=ID;
    Signature sig;
    privKey=sig.keyGen();
    pubKey=sig.pubKey;
    int transactionCount[8];
    int balances[8];
    for (int i=0;i<8;i++){
        balances[i]=0;
        oldBalances[i]=0;
        transactionCount[i]=0;
    }
    // First transaction in block is miner's reward
    currentBlock.setContent(1, "", balances, transactionCount);
    currentBlock.balances[minerID+4]++;
    Transaction transaction;
    string kek="SYSTEM";
    transaction.addData(0, kek, pubKey, 1);
    currentBlock.addTransaction(transaction);
    //cout << currentBlock.i << endl;
    zeros="000000000000000000000000000000";
    thread thr(mining, this, difficulty);
    thr.detach();
}





void Miner::sendBlock(){
    (*mtx).lock();
    for (int i=0; i<4; i++){
        if (i!=minerID){
            miner[i].setBlock(currentBlock);
        }
        user[i].setBlock(currentBlock);
    }
    (*mtx).unlock();
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
        if (currentBlock.balances[newSenderID]>=(*setTransaction).value){
            (*mtx).lock();
            currentBlock.addTransaction(*setTransaction);
            currentBlock.balances[newSenderID]=currentBlock.balances[newSenderID]-(*setTransaction).value;
            currentBlock.balances[newReceiverID]=currentBlock.balances[newReceiverID]+(*setTransaction).value;
            currentBlock.transactionCount[newSenderID]++;
            (*mtx).unlock();
            cout << "MINER " << minerID+1 << ": " << "Transaction was added to the block" << endl;
        }
        else{
            cout << "MINER " << minerID+1 << ": " << "You have not enough money" << endl;
        }
    }
    else{
        cout << "MINER " << minerID+1 << ": " << "Invalid transaction" << endl;
    }
}







void Miner::setBlock(Block newReceivedBlock){
    if ((newReceivedBlock.hashFunc()==newReceivedBlock.hash) && (newReceivedBlock.number==currentBlock.number) && (newReceivedBlock.prevHash==currentBlock.prevHash)){
        int error=0;
        if (newReceivedBlock.transactions[0].value!=1 && newReceivedBlock.transactions[0].sender!="SYSTEM"){
            error=1;
        }
        else{
            int sumBalances[8];
            for (int j=0; j<8; j++){
                sumBalances[j]=oldBalances[j];
            }
            int receiverID;
            int senderID;
            for (int j=0; j<4; j++){ // Finding the ID of sender and receiver
                if (newReceivedBlock.transactions[0].receiver==miner[j].pubKey){
                    receiverID=j+4;
                }
            }
            sumBalances[receiverID]++;
            for (int i=1; i<newReceivedBlock.i; i++){
                if (!newReceivedBlock.transactions[i].check() || newReceivedBlock.transactions[i].value<=0){
                    error=2;
                    break;
                }
                for (int j=0; j<4; j++){ // Finding the ID of sender and receiver
                    if (newReceivedBlock.transactions[i].sender==user[j].pubKey){
                        senderID=j;
                    }
                    else if (newReceivedBlock.transactions[i].receiver==user[j].pubKey){
                        receiverID=j;
                    }
                    if (newReceivedBlock.transactions[i].sender==miner[j].pubKey){
                        senderID=j+4;
                    }
                    else if (newReceivedBlock.transactions[i].receiver==miner[j].pubKey){
                        receiverID=j+4;
                    }
                }
                sumBalances[receiverID]=sumBalances[receiverID]+newReceivedBlock.transactions[i].value; // Balances check
                sumBalances[senderID]=sumBalances[senderID]-newReceivedBlock.transactions[i].value;
            }
            for (int i=0; i<8; i++){
                if ((sumBalances[i]!=newReceivedBlock.balances[i]) && (error==0)){
                    error=3;
                }
            }
        }
        if (error==0){
            //cout << "MINER " << minerID+1 << ": " << "Block is valid" << endl;
            receivedBlock=newReceivedBlock;
            blockAvailable=true;
        }
        else{
            cout << "MINER " << minerID+1 << ": " << "Block is invalid, error: " << error << endl;
        }
    }
}






void Miner::mining(int difficulty){
    while(true){
        zeros=zeros.substr(0, difficulty);
        while (currentBlock.hashFunc().substr(0, difficulty)!=zeros){
            currentBlock.nonce++;
            if (blockAvailable){
                currentBlock=receivedBlock;
            }
        }
        if (!blockAvailable){
            currentBlock.hash=currentBlock.hashFunc();
            cout << "Block has been found by miner " << minerID+1 << endl;
            sendBlock();
        }
        else{
            blockAvailable=false;
        }
        currentBlock.setContent(currentBlock.number+1, currentBlock.hash, currentBlock.balances, currentBlock.transactionCount);
        for (int j=0; j<8; j++){
            oldBalances[j]=currentBlock.balances[j];
        }
        currentBlock.balances[4+minerID]++;
        Transaction transaction;
        string kek="SYSTEM";
        transaction.addData(0, kek, pubKey, 1);
        currentBlock.addTransaction(transaction);
        zeros="000000000000000000000000000000";
    }
}
