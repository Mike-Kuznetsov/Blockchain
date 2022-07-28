/*
*   Blockchain for Mautoz Tech Youtube Video.
*   In this project i write simpliest cryptocurrency for my youtube channel.
*   Version 2.1 Added transactions
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
#include <shared_mutex>
#include "miner.h"
#include "user.h"
#include "signature.h"
#include "transaction.h"
using namespace std;

int main(int argc, char *argv[])
{
    int difficulty=5;
    mutex mtx;
    User *user = new User[4];
    Miner *miner= new Miner[4];
    string pubKeys[8];
    for (int i=0; i<4; i++){
        pubKeys[i]=user[i].pubKey;
        pubKeys[i+4]=miner[i].pubKey;
    }
    for (int i=0; i<4; i++){
        miner[i].start(user, miner, i, &mtx, difficulty, pubKeys);
        user[i].start(i, difficulty, user, pubKeys);
    }
    string input;
    cmatch result;
    int ID;
    regex regexBalances("(balances|bal)", regex_constants::icase);
    regex regexTransfer("(send|transfer|add|transaction)""[ ]""([1-8])""[ ]""([1-8])""[ ]""([0-9]{1,4})", regex_constants::icase);
    regex regexShowChain("(showchain|sc)""[ ]?""([1-8]?)", regex_constants::icase);
    regex regexCheck("check", regex_constants::icase);
    regex regexStop("stop", regex_constants::icase);
    cout << "Commands:" << endl;
    cout << "showChain (sc) [1-8] - to show hashes of blocks in user's [1-4] or miner's [5-8] blockchain" << endl;
    cout << "check - to check every blockchain" << endl;
    cout << "balances (bal) - to output balance of every user's wallet" << endl;
    cout << "send [FROM(1-8)] [TO(1-8)] [AMOUNT(int)] - to add new transaction to blockchain" << endl;
    while(true){
        getline (cin, input);
        if (regex_match(input.c_str(), result, regexBalances)){ // Processing "balance" command
            cout << "Verified balances:" << endl;
            for (int i=0;i<4;i++){
                cout << "User " << i+1 << " balance: " << user[0].block[user[0].lastBlock].balances[i] << endl;
            }
            for (int i=0;i<4;i++){
                cout << "Miner " << i+1 << " balance: " << user[0].block[user[0].lastBlock].balances[4+i] << endl;
            }
         }
         else if (regex_match(input.c_str(), result, regexShowChain)){ // Processing "showChain" command
            if (result[2]!=""){
                ID=stoi(result[2])-1;
            }
            else{
                ID=0;
            }
            if (ID>3){
                cout << "Outputting hashes from blockchain of miner: " << ID-4 << endl;
                miner[ID-4].showChain();
            }
            else{
                cout << "Outputting hashes from blockchain of user: " << ID << endl;
                user[ID].showChain();
            }
         }
         else if (regex_match(input.c_str(), result, regexCheck)){ // Processing "check" command
            for (int i=0;i<4;i++){
                if (user[i].check()){
                    cout << "User " << i <<" - Blockchain is valid" << endl;
                }
                else{
                    cout << "User " << i <<" - Blockchain is corrupted" << endl;
                }
            }
            for (int i=0;i<4;i++){
                if (miner[i].check()){
                    cout << "Miner " << i <<" - Blockchain is valid" << endl;
                }
                else{
                    cout << "Miner " << i <<" - Blockchain is corrupted" << endl;
                }
            }
         }
         else if (regex_match(input.c_str(), result, regexTransfer)){ // Processing "add transaction" command
            // result: 2 = FROM, 3 = TO, 4 = AMOUNT
            int senderID = stoi(result[2].str())-1;
            int receiverID = stoi(result[3].str())-1;
            int value=stoi(result[4].str());
            int transactionCount=0;
            for (int i=0; i<4; i++){
                if (miner[i].block[miner[i].lastBlock+1].transactionCount[senderID]>transactionCount){
                    transactionCount=miner[i].block[miner[i].lastBlock+1].transactionCount[senderID];
                }
            }
            transactionCount++;
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
            for (int i=0; i<4; i++){
                miner[i].addTransaction(&transaction);
            }
         }
         else if (regex_match(input.c_str(), result, regexStop)){
             return 1;
         }
         else{
            cout << "No such command" << endl;
         }
    }
    return 0;
}
