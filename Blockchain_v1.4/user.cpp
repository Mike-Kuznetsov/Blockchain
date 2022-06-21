#include <iostream>
#include "user.h"
#include "block.h"
//#include "main.cpp"
//#include "miner.h"
//#include <thread>

using namespace std;

        User::User(){
            block[0].setContent(0, "");
            lastBlock=0;
        }
        void User::setBlock(Block receivedBlock){
            if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
                lastBlock++;
                block[lastBlock]=receivedBlock;
            }
            //  Note for the future: ELSE we'll compare it with different blockchains and if it's wrong miner we'll be banned.
            // ELSE Сравнение своего блокчейна с другими блокчейнами и бан майнера приславшего блок
            // + Функция для получения всего блокчейна и его проверка
        }
        bool User::check(){
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
        void User::showChain(){
            for (int i=0; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].prevHash << endl;
                cout <<  block[i].hash << endl;
            }
        }
        void User::showData(){
            for (int i=0; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].data << endl;
            }
        }
