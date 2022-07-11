/*
*   Blockchain for Mautoz Tech Youtube Video.
*   In this project i write simpliest cryptocurrency for my youtube channel.
*   Version 2.5 Refactored. Bugfixes.
*   OpenSSL Library required.
*
*   Mautoz Tech - https://www.youtube.com/c/MautozTech
*   Заметки ESPшника - https://www.youtube.com/channel/UCQAbEIaWFdARXKqcufV6y_g
*
*    This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*    This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*    You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <regex>
#include "miner.h"
#include "user.h"
#include "signature.h"
#include "transaction.h"
using namespace std;

void showCommands(){
    cout << "balances (bal) - to output balance of every user's wallet" << endl;
    cout << "send [FROM(1-8)] [TO(1-8)] [AMOUNT(int)] - to add new transaction to blockchain" << endl;
}
int main(int argc, char *argv[])
{
    /*Signature signature[8];
    Signature *ptr=signature;
    string privateKeys[8];
    for (int i=0; i<8; i++){
        privateKeys[i]=signature[i].keyGen();
    }*/
    User *user = new User[4];
    Miner *miner= new Miner[4];
    for (int i=0; i<4; i++){
        //user[i].init(i);
        miner[i].start(user, miner, i);
    }
    string pubKeys[8];
    for (int i=0; i<4; i++){
        pubKeys[i]=user[i].pubKey;
        pubKeys[i+4]=miner[i].pubKey;
    }
    for (int i=0; i<4; i++){
        user[i].init(pubKeys, i);
    }



    string input;
    cmatch result;
    int ID;
    regex regexBalances("(balances|bal)", regex_constants::icase);
    regex regexTransfer("(send|transfer|add|transaction)""[ ]""([1-8])""[ ]""([1-8])""[ ]""([0-9]{1,4})", regex_constants::icase);
    regex regexStop("(stop|s)", regex_constants::icase);
    cout << "Commands:" << endl;
    showCommands();
    //cout << "Every other sequence of symbols - to write symbols into current block which is being mined" << endl;
    while(true){
        getline (cin, input);
        if (regex_match(input.c_str(), result, regexBalances)){ // Processing "balance" command
            for (int i=0;i<4;i++){
                cout << "User " << i+1 << " balance: " << user[0].block[user[0].lastBlock].balances[i] << endl;
            }
            for (int i=0;i<4;i++){
                cout << "Miner " << i+1 << " balance: " << user[0].block[user[0].lastBlock].balances[4+i] << endl;
            }
            /*for (int i=0;i<9;i++){
                cout << user[0].block[user[0].lastBlock].transactionCount[i] << endl;
            }*/
         }
         else if (regex_match(input.c_str(), result, regexTransfer)){ // Processing "add transaction" command
            // result: 2 = FROM, 3 = TO, 4 = AMOUNT
            int senderID = stoi(result[2].str())-1;
            int receiverID = stoi(result[3].str())-1;
            int value=stoi(result[4].str());
            int transactionCount=0;
            for (int i=0; i<4; i++){
                if (miner[i].currentBlock.transactionCount[senderID]>transactionCount){
                    transactionCount=miner[i].currentBlock.transactionCount[senderID];
                }
            }
            Transaction transaction;
            if (senderID<4){
                if (receiverID<4){
                    transaction.addData(transactionCount, user[senderID].pubKey, user[receiverID].pubKey, value);
                }
                else{
                    transaction.addData(transactionCount, user[senderID].pubKey, miner[receiverID-4].pubKey, value);
                }
                transaction.sign(&user[senderID].privKey);
            }
            else{
                if (receiverID<4){
                    transaction.addData(transactionCount, miner[senderID-4].pubKey, user[receiverID].pubKey, value);
                }
                else{
                    transaction.addData(transactionCount, miner[senderID-4].pubKey, miner[receiverID-4].pubKey, value);
                }
                transaction.sign(&miner[senderID-4].privKey);
            }
            //cout << transaction.check() << endl;
            for (int i=0; i<4; i++){
                miner[i].addTransaction(&transaction);
            }
         }
         else if (regex_match(input.c_str(), result, regexStop)){
             return 1;
         }
         else{
            cout << "Wrong command, here's command list: " << endl;
            showCommands();
         }
    }
    return 0;
}
