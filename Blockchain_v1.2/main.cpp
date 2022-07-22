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
    int difficulty = 5;
    Miner miner;
    User user[4];
    miner.start(user, &mtx, difficulty);
    for (int i=0; i<4; i++){
        user[i].start(difficulty);
    }
    cmatch result;
    regex regexShowData("(showdata|sd)""[ ]?""([1-4]?)", regex_constants::icase);
    regex regexShowChain("(showchain|sc)""[ ]?""([1-4]?)", regex_constants::icase);
    regex regexCheck("check", regex_constants::icase);
    cout << "Commands:" << endl;
    cout << "showData (sd) [1-4] - to show data in user's [1-4] blockchain" << endl;
    cout << "showChain (sc) [1-4] - to show hashes of blocks in user's [1-4] blockchain" << endl;
    cout << "check - to check every blockchain" << endl;
    cout << "Every other sequence of symbols - to write symbols into current block which is being mined" << endl;
    string input;
    int ID;
    while(true){
         getline(cin, input);
         if (regex_match(input.c_str(), result, regexShowData)){ // Processing "showData" command
            if (result[2]!=""){
                cout << "Outputting data from blockchain of user: " << result[2] << endl;
                ID=stoi(result[2])-1;
            }
            else{
                cout << "Outputting data from blockchain of user: 1" << endl;
                ID=0;
            }
            user[ID].showData();
         }
         else if (regex_match(input.c_str(), result, regexShowChain)){ // Processing "showChain" command
            if (result[2]!=""){
                cout << "Outputting hashes from blockchain of user: " << result[2] << endl;
                ID=stoi(result[2])-1;
            }
            else{
                cout << "Outputting hashes from blockchain of user: 1" << endl;
                ID=0;
            }
            user[ID].showChain();
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
         }
         else{
            miner.addData(input);
            //miner[1].addData(input);
            //miner[2].addData(input);
            //miner[3].addData(input);
         }
    }
    /*while(true){
         cin >> input;
         if (input=="showData"){
            user[0].showData();
         }
         else if (input=="showChain"){
            user[0].showChain();
         }
         else if (input=="check"){
            if (user[0].check())
                cout << "Blockchain is valid" << endl;
            else
                cout << "Blockchain is corrupted" << endl;
            }
         else{
            miner.addData(input);
         }
    }*/
    return 0;
}