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
            Signature *signature;
            block[0].setContent(0, "", balances, transactionCount, signature);
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
            else cout << "NO";
            // ELSE ��������� ������ ��������� � ������� ����������� � ��� ������� ����������� ����
            // + ������� ��� ��������� ����� ��������� � ��� ��������
        }
        /*void User::addData(string newData){
            block[lastBlock].addData(newData);
        }*/
