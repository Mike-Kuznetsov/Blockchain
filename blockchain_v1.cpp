/* 
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 1. Added blockchain class to operate our blockchain.
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
#include "sha256.h"

using namespace std;

class Block {
    public:
        int number;
        string thisHash;
        string prevHash;
        string data;
        setContent(int setNumber, string setData, string setPrevHash){
            prevHash=setPrevHash;
            number=setNumber;
            data=setData;
            thisHash=getHash();
            /*cout << "Block number: " << number << endl;
            cout << "Previous Hash: " << prevHash << endl;
            cout << "Data: " << data << endl;
            cout << "Hash: " << thisHash << endl;
            cout << endl;
            cout << endl;*/
        }
        string getHash(){
            return sha256(to_string(number) + data + prevHash);
        }
};

class Blockchain {
    public:
        int lastBlock;
        Block block[10000];
  
        Blockchain(){
            block[0].setContent(0,"Data: First Block","0");
            lastBlock=0;
        }
 
        void newBlock(string data){
            lastBlock++;
            block[lastBlock].setContent(lastBlock,data,block[lastBlock-1].thisHash);
        }
  
        bool check(){
            for (int i=1; i<=lastBlock; i++){
                if (block[i].thisHash != block[i].getHash()){
                    return false;
                }
                else if (block[i].prevHash != block[i-1].thisHash){
                    return false;
                }
            }
            return true;
        }
};

int main(int argc, char *argv[])
{
    Blockchain myCoin;
    myCoin.newBlock("ABCDEFG");
    myCoin.newBlock("XYZ");
    if (myCoin.check())
        cout << "Blockchain is valid" << endl;
    else
        cout << "Blockchain is invalid" << endl;
    return 0;
}
