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
            block[0].setContent(0, "", balances, transactionCount, signature);
            lastBlock=0;
        }
        void User::setPrivKey(string *setPrivKey){
            privKey=setPrivKey;
        }
        void User::setBlock(Block receivedBlock){
            //cout << "User's setBlock" << endl;
            if ((receivedBlock.hashFunc()==receivedBlock.hash) && (receivedBlock.number==block[lastBlock].number+1) && (receivedBlock.prevHash==block[lastBlock].hash)){
                cout << "Block is valid" << endl;
                cout << receivedBlock.i << " transactions in block" << endl;
                bool noErrors=true;
                if (receivedBlock.transactions[0].value!=1){
                    noErrors=false;
                }
                else{
                    for (int i=1; i<receivedBlock.i; i++){
                    //cout << "transaction checking" << endl;
                    //cout << "OUTPUT/SIGN: " << receivedBlock.transactions[i].signature << endl;
                        if (receivedBlock.transactions[i].hashFunc()!=reinterpret_cast<char*>((*signature).decrypt(&receivedBlock.transactions[i].signature, &receivedBlock.transactions[i].sender))){
                            cout << i << " transaction is invalid" << endl;
                            noErrors=false;
                        }
                    }
                }
                if (noErrors){
                    lastBlock++;
                    block[lastBlock]=receivedBlock;
                }
            }
            else if (receivedBlock.hashFunc()!=receivedBlock.hash){
                cout << "Incorrect hash" << endl;
                //cout << "Miner: " << *receivedBlock.transactions[0].sender << endl;
            }
            else if (receivedBlock.number!=block[lastBlock].number+1){
                cout << "Incorrect block number" << endl;
                //cout << "Miner: " << *receivedBlock.transactions[0].sender << endl;
            }
            else if (receivedBlock.prevHash!=block[lastBlock].hash){
                cout << "Incorrect prevHash" << endl;
                //cout << "Miner: " << *receivedBlock.transactions[0].sender << endl;
            }
            else{
                cout << "IDK WHAT'S WRONG" << endl;
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
