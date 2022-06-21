/*
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 1.3. Added header files
*   In this project i write simpliest cryptocurrency for my youtube channel.
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
using namespace std;

int main(int argc, char *argv[])
{
    User *user = new User[4];
    Miner *miner= new Miner[4];
    for (int i=0; i<4; i++){
        miner[i].start(user, miner, i);
    }
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
            miner[1].addData(input);
            miner[2].addData(input);
            //miner[3].addData(input);
         }
    }
    return 0;
}
