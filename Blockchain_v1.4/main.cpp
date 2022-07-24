#include <iostream>
#include "user.h"
#include "miner.h"
#include <thread>
#include <mutex>
#include <regex>
using namespace std;
mutex mtx;

int main()
{
    int difficulty = 6;
    Miner miner[4];
    User user[4];
    for (int i=0; i<4; i++){
        user[i].start(difficulty, i, user);
        miner[i].start(user, &mtx, difficulty, miner, i);
    }
    cmatch result;
    regex regexShowData("(showdata|sd)""[ ]?""([1-8]?)", regex_constants::icase);
    regex regexShowChain("(showchain|sc)""[ ]?""([1-8]?)", regex_constants::icase);
    regex regexCheck("check", regex_constants::icase);
    cout << "Commands:" << endl;
    cout << "showData (sd) [1-8] - to show data in user's [1-4] or miner's [5-8] blockchain" << endl;
    cout << "showChain (sc) [1-8] - to show hashes of blocks in user's [1-4] or miner's [5-8] blockchain" << endl;
    cout << "check - to check every blockchain" << endl;
    cout << "Every other sequence of symbols - to write symbols into current block which is being mined" << endl;
    string input;
    int ID;
    while(true){
         getline(cin, input);
         if (regex_match(input.c_str(), result, regexShowData)){ // Processing "showData" command
            if (result[2]!=""){
                ID=stoi(result[2])-1;
            }
            else{
                ID=0;
            }
            if (ID>3){
                cout << "Outputting data from blockchain of miner: " << ID-4 << endl;
                miner[ID-4].showData();
            }
            else{
                cout << "Outputting data from blockchain of user: " << ID << endl;
                user[ID].showData();
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
         else if (input=="stop"){
            break;
         }
         else{
            for (int i=0; i<4; i++){
                miner[i].addData(input);
            }
         }
    }
    return 0;
}
