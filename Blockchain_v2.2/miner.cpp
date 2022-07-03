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
            currentBlock.setContent(1, "", balances, transactionCount);
            //currentBlock.addTransaction("MINER "+to_string(minerID)+" -");
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
        void Miner::addTransaction(string newData){
            //currentBlock.addTransaction(newData);
        }
        void Miner::setBlock(Block newReceivedBlock){
            if ((newReceivedBlock.hashFunc()==newReceivedBlock.hash) && (newReceivedBlock.number==currentBlock.number) && (newReceivedBlock.prevHash==currentBlock.prevHash)){
                //cout << "BlockAvailable set to True" << endl;
                receivedBlock=newReceivedBlock;
                blockAvailable=true;
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
                    //cout << "Block has been found" << endl;
                    //cout << "HASH: " << currentBlock.hash << endl;
                    sendBlock();
                }
                else{
                    blockAvailable=false;
                }
                Transaction transaction; // может переделать
                string kek="SYSTEM";
                transaction.addData(currentBlock.transactionCount[8], &(kek), &(signature[4+minerID].pubKey), 1);
                transaction.sign(privKey);
                currentBlock.transactionCount[8]++;
                currentBlock.balances[4+minerID]++;
                currentBlock.setContent(currentBlock.number+1, currentBlock.hash, currentBlock.balances, currentBlock.transactionCount);
                zeros="000000000000000000000000000000";
                //currentBlock.addTransaction("MINER "+to_string(minerID)+" - ");
                //cout << "MINER " << to_string(minerID) << endl;
            }
        }
