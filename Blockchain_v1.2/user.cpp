#include <iostream>
#include "block.cpp"
#include <thread>

using namespace std;

class User {
    public:
        int lastBlock;
        Block block[10000];

        User(){
            block[0].setContent(0,"");
            lastBlock=0;
        }
        void setBlock(Block receivedBlock){
            if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
                lastBlock++;
                block[lastBlock]=receivedBlock;
            }
            // Note for the future: ELSE we'll compare it with different blockchains and if it's wrong miner we'll be banned.

        }
        bool check(){
            for (int i=1; i<lastBlock; i++){
                if (block[i].hash != block[i].hashFunc()){
                    return false;
                }
                else if (block[i].prevHash != block[i-1].hash){
                    return false;
                }
            }
            return true;
        }
        void showChain(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].prevHash << endl;
                cout <<  block[i].hash << endl;
            }
            cout << "Chain" << endl;
        }
        void showData(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].data << endl;
            }
        }

};
