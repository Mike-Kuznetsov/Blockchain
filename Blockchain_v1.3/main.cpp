#include <iostream>
#include <regex>
#include "miner.h"
#include "user.h"
using namespace std;

/*class Transaction {
    public:
        int number, value;
        string sender, receiver, sign;
};*/


int main(int argc, char *argv[])
{
    User *user = new User[4];
    Miner *miner= new Miner[4];
    miner[0].start(user); // miner
    //miner[1].start(user, miner);
    //user1.setMiners(miner1);
    string input;
    cmatch result;
    int ID;
    regex regexShowData("(showdata|sd)""[ ]?""([1-4]?)", regex_constants::icase);
    regex regexShowChain("(showchain|sc)""[ ]?""([1-4]?)", regex_constants::icase);
    regex regexCheck("check""[ ]?""([1-4]?)", regex_constants::icase);
    cout << "Commands:" << endl;
    cout << "showData (sd) [1-4] - to show data in user's [1-4] blockchain" << endl;
    cout << "showChain (sc) [1-4] - to show hashes of blocks in user's [1-4] blockchain" << endl;
    cout << "check [1-4] - to check the blockchains of user [1-4] or all users" << endl;
    cout << "Every other sequence of symbols - to write symbols into current block which is being mined" << endl;
    while(true){
         getline (cin, input);
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
            if (result[1]!=""){
                cout << "Checking blockchain of user: " << result[1] << endl;
                if (user[stoi(result[1])-1].check())
                    cout << "Blockchain is valid" << endl;
                else
                    cout << "Blockchain is corrupted" << endl;
            }
            else{
                for (int i=0;i<4;i++){
                    if (user[i].check()){
                        cout << "User " << i <<" - Blockchain is valid" << endl;
                    }
                    else{
                        cout << "User " << i <<" - Blockchain is corrupted" << endl;
                    }
                }
            }
         }
         else{
            miner[0].addData(input);
            //miner[1].addData(input);
            //miner[2].addData(input);
            //miner[3].addData(input);
         }
    }
    return 0;
}
