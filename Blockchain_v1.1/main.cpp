/* 
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 1.1. Now classes are in separate files. Class Blockchain has been divided into classes User and Miner. 
*   When miner finds block it sends it to user which collects correct blocks into blockchain.
*   This program is simpliest implementation of blockchain technology.
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
#include "miner.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    User user1;
    Miner miner1;
    miner1.start(&user1);
    string input;
    while(true){
         cin >> input;
         if (input=="showData"){
            user1.showData();
         }
         else if (input=="showChain"){
            user1.showChain();
         }
         else if (input=="check"){
            if (user1.check())
                cout << "Blockchain is valid" << endl;
            else
                cout << "Blockchain is corrupted" << endl;
            }
         else{
            miner1.addData(input);
         }
    }
    return 0;
}
