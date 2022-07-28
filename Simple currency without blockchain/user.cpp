#include <iostream>
#include "user.h"

using namespace std;

/*User::User(){
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
void User::setBlock(Block receivedBlock){ // Inserting block into blockchain after checking hashes and balances
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
                if (receivedBlock.transactions[0].receiver==pubKeys[j]){
                    receiverID=j;
                }
            }
            balances[receiverID]++;
            for (int i=1; i<receivedBlock.i; i++){
                if (!receivedBlock.transactions[i].check() || receivedBlock.transactions[i].value<=0){ // Transactions check
                    error=2;
                    break;
                }
                for (int j=0; j<8; j++){ // Finding the ID of sender and receiver
                    if (receivedBlock.transactions[i].sender==pubKeys[j]){
                        senderID=j;
                    }
                    else if (receivedBlock.transactions[i].receiver==pubKeys[j]){
                        receiverID=j;
                    }
                }
                balances[receiverID]=balances[receiverID]+receivedBlock.transactions[i].value; // Balances check
                balances[senderID]=balances[senderID]-receivedBlock.transactions[i].value;
            }
            for (int i=0; i<8; i++){
                if (balances[i]!=receivedBlock.balances[i]){
                    error=3;
                }
            }

        }
        if (error==0){ // if correct
            lastBlock++;
            block[lastBlock]=receivedBlock;
        }
        else{
            cout << "USER: Block is invalid, error: " << error << endl;
        }
    }
}*/

