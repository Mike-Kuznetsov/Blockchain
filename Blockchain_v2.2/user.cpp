#include <iostream>
#include "user.h"
#include "block.h"

using namespace std;

        User::User(){
            int balances[9];
            int transactionCount[9];
            for (int i=0;i<9;i++){
                balances[i]=0;
                transactionCount[i]=0;
            }
            block[0].setContent(0, "", balances, transactionCount);
            lastBlock=0;
        }
        void User::setPrivKey(string *setPrivKey){
            privKey=setPrivKey;
        }
        void User::setBlock(Block receivedBlock){
            if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
                lastBlock++;
                block[lastBlock]=receivedBlock;
            }
            // ELSE Сравнение своего блокчейна с другими блокчейнами и бан майнера приславшего блок
            // + Функция для получения всего блокчейна и его проверка
        }
        /*void User::addData(string newData){
            block[lastBlock].addData(newData);
        }*/
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
