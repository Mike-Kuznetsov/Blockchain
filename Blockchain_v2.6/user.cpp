#include <iostream>
//#include "miner.h"
#include "user.h"
#include "block.h"
#include "signature.h"

using namespace std;

User::User(){
    int balances[8];
    int transactionCount[8];
    Signature sig;
    privKey=sig.keyGen();
    pubKey=sig.pubKey;
    for (int i=0;i<8;i++){
        balances[i]=0;
        transactionCount[i]=0;
    }
    Signature *signature;
    block[0].setContent(0, "", balances, transactionCount);
    lastBlock=0;
}
void User::init(string *setPubKeys, int ID){
    userID=ID;
    pubKeys=setPubKeys;
}
void User::setBlock(Block receivedBlock){
    if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){ // Block hashes check
        int error=0;
        if (receivedBlock.transactions[0].value!=1 && receivedBlock.transactions[0].sender!="SYSTEM"){ // First Block check
            error=1;
        }
        else{
            int balances[8];
            for (int i=0; i<8; i++){
                balances[i]=block[lastBlock].balances[i];
            }
            int receiverID;
            int senderID;
            for (int j=0; j<8; j++){ // Finding the ID of sender and receiver
                //if (userID==0) cout << pubKeys[j] << endl;
                if (receivedBlock.transactions[0].receiver==pubKeys[j]){
                    receiverID=j;
                }
            }
            balances[receiverID]++;
            //cout << "Found = " << receiverID << "Bal: " << balances[receiverID] << endl;
            for (int i=1; i<receivedBlock.i; i++){
                if (!receivedBlock.transactions[i].check() || receivedBlock.transactions[i].value<=0){ // Transactions check
                    error=2;
                    break;
                }
                //cout << userID << "KEK1" << endl;
                for (int j=0; j<8; j++){ // Finding the ID of sender and receiver
                    if (receivedBlock.transactions[i].sender==pubKeys[j]){
                        senderID=j;
                    }
                    else if (receivedBlock.transactions[i].receiver==pubKeys[j]){
                        receiverID=j;
                    }
                }
                //cout << userID << "KEK2" << endl;
                balances[receiverID]=balances[receiverID]+receivedBlock.transactions[i].value; // Balances check
                balances[senderID]=balances[senderID]-receivedBlock.transactions[i].value;
            }
            for (int i=0; i<8; i++){
                if (balances[i]!=receivedBlock.balances[i]){
                    //cout << endl;
                    error=3;
                }
            }
            /*if (error==3){
                for (int i=0; i<8; i++){
                        //cout << balances[i] << " ";
                    }
                    //cout << endl;
                    for (int i=0; i<8; i++){
                        //cout << receivedBlock.balances[i] << " ";
                    }
                    //cout << endl;
            }*/
        }
        if (error==0){
            lastBlock++;
            block[lastBlock]=receivedBlock;
            //cout << "Block is valid" << endl;
        }
        else{
            cout << "Block is invalid, error: " << error << endl;
        }
    }
}

