#include <iostream>
#include "miner.h"
#include "block.h"
#include "user.h"
#include <thread>
#include "transaction.h"
using namespace std;

        void Miner::start(User *user1, Miner *miner1, int ID, Signature *ptr, string *setPrivKey){
            user=user1;
            miner=miner1;
            minerID=ID;
            signature=ptr;
            privKey=setPrivKey;
            int balances[9];
            int transactionCount[9];
            for (int i=0;i<9;i++){
                balances[i]=0;
                transactionCount[i]=0;
            }
            // First transaction in block is miner's reward
            Transaction transaction;
            string kek="SYSTEM";
            transaction.addData(currentBlock.transactionCount[8], &(kek), &(signature[4+minerID].pubKey), 1);
            //cout << "MINER " << minerID+1 << endl;
            transaction.sign(privKey);
            currentBlock.setContent(1, "", balances, transactionCount, signature);
            currentBlock.addTransaction(&transaction);
            currentBlock.transactionCount[8]++;
            currentBlock.balances[4+minerID]++;
            zeros="000000000000000000000000000000";
            thread thr(mining, this, 6);
            thr.detach();
        }
        void Miner::sendBlock(){
            for (int i=0; i<4; i++){
                user[i].setBlock(currentBlock);
                if (i!=minerID){
                    //cout << "MINER ID - " << to_string(minerID) << " SENT TO: " << to_string(i) << " BLOCK NUM: " << currentBlock.number << endl;
                    miner[i].setBlock(currentBlock);
                }
            }
        }
        void Miner::addTransaction(Transaction setTransaction){
            int senderID=0;
            int receiverID=0;
            for (int j=0; j<8; j++){
                if (setTransaction.sender==currentBlock.signature[j].pubKey){
                    senderID=j;
                }
                else if (setTransaction.receiver==currentBlock.signature[j].pubKey){
                    receiverID=j;
                }
            }
            string str=setTransaction.hashFunc();
            cout << "HASH: " << str << endl;
            //cout << "HUEK: " << reinterpret_cast<char*>((*signature).decrypt(&setTransaction.signature, &setTransaction.sender)) << endl;
            if (currentBlock.balances[senderID]>=setTransaction.value){
                if (str==reinterpret_cast<char*>((*signature).decrypt(&setTransaction.signature, &setTransaction.sender))){
                    currentBlock.addTransaction(&setTransaction);
                    currentBlock.balances[senderID]=currentBlock.balances[senderID]-setTransaction.value;
                    currentBlock.balances[receiverID]=currentBlock.balances[receiverID]+setTransaction.value;
                    currentBlock.transactionCount[senderID]++;
                    cout << "Transfer completed" << endl;
                }
                else{
                    cout << "Incorrect signature" << endl;
                }
            }
            else{
                cout << "You have not enough money" << endl;
            }
            /*for (int j=0; j<8; j++){

                cout << currentBlock.balances[j] << endl;
            }*/
        }
        void Miner::setBlock(Block newReceivedBlock){
            if ((newReceivedBlock.hashFunc()==newReceivedBlock.hash) && (newReceivedBlock.number==currentBlock.number) && (newReceivedBlock.prevHash==currentBlock.prevHash)){
                //cout << "BlockAvailable set to True" << endl;
                bool noErrors=true;
                if (newReceivedBlock.transactions[0].value!=1){
                    noErrors=false;
                }
                else{
                    int recordedBalances2[9];
                    for (int i=0; i<9; i++){
                        recordedBalances2[i]=recordedBalances[i];
                    }
                    for (int i=1; i<newReceivedBlock.i; i++){
                        //cout << "transaction checking" << endl;
                        //cout << "OUTPUT/SIGN: " << receivedBlock.transactions[i].signature << endl;
                        Signature signature2;
                        string kek=newReceivedBlock.transactions[i].hashFunc();
                        cout << "HASH2: " << kek << endl;
                        if (kek!=reinterpret_cast<char*>(signature2.decrypt(&newReceivedBlock.transactions[i].signature, &newReceivedBlock.transactions[i].sender))){
                            cout << "MINER " << minerID << " " << i << " transaction is invalid" << endl;
                            noErrors=false;
                        }
                        /*else{
                            cout << "MINER " << minerID << " " << i << " transaction is valid" << endl;
                        }*/
                    }
                }
                if (noErrors){
                    receivedBlock=newReceivedBlock;
                    blockAvailable=true;
                }
            }
        }
        void Miner::mining(int difficulty){
            while(true){
                //Transaction transaction();
                zeros=zeros.substr(0, difficulty);
                while (currentBlock.hashFunc().substr(0, difficulty)!=zeros){
                    currentBlock.nonce++;
                    if (blockAvailable){
                        currentBlock=receivedBlock;
                        //cout << "MINER " << to_string(minerID) << "BLOCK AVAILABLE" << endl;
                    }
                }
                if (!blockAvailable){
                    currentBlock.hash=currentBlock.hashFunc();
                    cout << "Block has been found by miner " << minerID+1 << endl;
                    //cout << "HASH: " << currentBlock.hash << endl;
                    sendBlock();
                }
                else{
                    blockAvailable=false;
                }
                Transaction transaction; // может переделать
                string kek="SYSTEM";
                //cout << "system";
                transaction.addData(currentBlock.transactionCount[8], &(kek), &(signature[4+minerID].pubKey), 1);
                transaction.sign(privKey);
                currentBlock.setContent(currentBlock.number+1, currentBlock.hash, currentBlock.balances, currentBlock.transactionCount, signature);
                currentBlock.transactionCount[8]++;
                currentBlock.balances[4+minerID]++;
                currentBlock.addTransaction(&transaction);
                for (int i=0; i<9; i++){
                    recordedBalances[i]=currentBlock.balances[i];
                }
                zeros="000000000000000000000000000000";
                //currentBlock.addTransaction("MINER "+to_string(minerID)+" - ");
                //cout << "MINER " << to_string(minerID) << endl;
            }
        }
