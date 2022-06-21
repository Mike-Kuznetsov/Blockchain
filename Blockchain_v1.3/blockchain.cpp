#include <iostream>
#include "blockchain.h"
#include "block.h"
#include <thread>

using namespace std;

        Blockchain::Blockchain(){
            block[0].setContent(0,"0");
            lastBlock=0;
            zeros="000000000000000000000000000000";
            thread thr(mining, this, 5);
            thr.detach();
        }
        void Blockchain::newBlock(){
            lastBlock++;
            block[lastBlock].setContent(lastBlock, block[lastBlock-1].hash);
            zeros="000000000000000000000000000000";

        }
        void Blockchain::addData(string newData){
            block[lastBlock].addData(newData);
        }
        bool Blockchain::check(){
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
        void Blockchain::mining(int difficulty){
            while(true){
                zeros=zeros.substr(0, difficulty);
                while (block[lastBlock].hashFunc().substr(0, difficulty)!=zeros){
                    block[lastBlock].nonce++;
                }
                block[lastBlock].hash=block[lastBlock].hashFunc();
                cout << "Block has been found" << endl;
                //cout << "HASH: " << block[lastBlock].hash << endl;
                newBlock();
            }
        }
        void Blockchain::showChain(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].prevHash << endl;
                cout <<  block[i].hash << endl;
            }
        }
        void Blockchain::showData(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].data << endl;
            }
        }
