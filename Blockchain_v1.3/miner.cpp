#include <iostream>
#include "miner.h"
#include "block.h"
#include "user.h"
#include <thread>

using namespace std;

        Miner::Miner(){
            currentBlock.setContent(1,"");
            zeros="000000000000000000000000000000";
        }
        void Miner::start(User *user1){// Miner *miner1
            user=user1;
            thread miner(mining, this, 5);
            miner.detach();
        }
        void Miner::sendBlock(){
            for (int i=0; i<4; i++){
                user[i].setBlock(currentBlock);
            }
            currentBlock.setContent(currentBlock.number+1, currentBlock.hash);
            zeros="000000000000000000000000000000";
        }
        void Miner::addData(string newData){
            currentBlock.addData(newData);
        }
        /*void setBlock(int nonce){
        }*/
        void Miner::mining(int difficulty){
            while(true){
                zeros=zeros.substr(0, difficulty);
                while (currentBlock.hashFunc().substr(0, difficulty)!=zeros){
                    currentBlock.nonce++;
                    //cout << block.nonce << endl;
                }
                currentBlock.hash=currentBlock.hashFunc();
                //cout << "Block has been found" << endl;
                //cout << "HASH: " << currentBlock.hash << endl;
                sendBlock();
            }
        }
