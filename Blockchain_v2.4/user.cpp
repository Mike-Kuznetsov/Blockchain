#include <iostream>
#include "user.h"
#include "block.h"
#include "signature.h"

using namespace std;

        User::User(){
            int balances[9];
            int transactionCount[9];
            for (int i=0;i<9;i++){
                balances[i]=0;
                transactionCount[i]=0;
            }
            Signature *signature;
            block[0].setContent(0, "", balances, transactionCount, signature);
            lastBlock=0;
        }
        void User::setBlock(Block receivedBlock){
            if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
                bool noErrors=true;
                if (receivedBlock.transactions[0].value!=1 && receivedBlock.transactions[0].sender!="SYSTEM"){
                    noErrors=false;
                }
                else{
                    for (int i=1; i<receivedBlock.i; i++){
                        if (!receivedBlock.transactions[i].check()){
                            noErrors=false;
                            break;
                        }
                    }
                }
                if (noErrors){
                    lastBlock++;
                    block[lastBlock]=receivedBlock;
                    //cout << "Block is valid" << endl;
                }
                else{
                    cout << "Block is invalid" << endl;
                }
            }
        }

