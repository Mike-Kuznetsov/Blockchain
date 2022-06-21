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
        void Miner::start(User *user1, Miner *miner1, int ID){//Miner *miner1
            user=user1;
            miner=miner1;
            minerID=ID;
            currentBlock.addData("MINER "+to_string(minerID)+" -");
            thread thr(mining, this, 6);
            thr.detach();
        }
        void Miner::sendBlock(){
            for (int i=0; i<4; i++){
                user[i].setBlock(currentBlock);
                if (i!=minerID){
                    miner[i].setBlock(currentBlock);
                }
            }
        }
        void Miner::addData(string newData){
            currentBlock.addData(newData);
        }
        void Miner::setBlock(Block newReceivedBlock){
            if ((newReceivedBlock.hashFunc()==newReceivedBlock.hash) && (newReceivedBlock.number==currentBlock.number) && (newReceivedBlock.prevHash==currentBlock.prevHash)){
                receivedBlock=newReceivedBlock;
                blockAvailable=true;
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
                    //cout << "Block has been found" << endl;
                    //cout << "HASH: " << currentBlock.hash << endl;
                    sendBlock();
                }
                else{
                    blockAvailable=false;
                }
                currentBlock.setContent(currentBlock.number+1, currentBlock.hash);
                zeros="000000000000000000000000000000";
                currentBlock.addData("MINER "+to_string(minerID)+" - ");
            }
        }
