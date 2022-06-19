#include <iostream>
#include "user.cpp"
#include <thread>

using namespace std;

class Miner {
    public:
        User* user;
        std::string zeros;
        Block currentBlock;

        Miner(){
            currentBlock.setContent(1,"");
            zeros="000000000000000000000000000000";

        }
        void sendBlock(){
            (*user).setBlock(currentBlock);
            currentBlock.setContent(currentBlock.number+1, currentBlock.hash);
            zeros="000000000000000000000000000000";
        }
        void start(User *user1){
            user = user1;
            thread miner(mining, this, 5);
            miner.detach();
        }
        void addData(string newData){
            currentBlock.addData(newData);
        }
        void mining(int difficulty){
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
};

