/* 
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 0.2. Added blockchain class for operating blockchain.
*   This program is the simpliest implementation of blockchain technology.
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
        string hash;
        string prevHash;
        string data;
        setContent(int setNumber, string setData, string setPrevHash){
            prevHash=setPrevHash;
            number=setNumber;
            data=setData;
            hash=hashFunc();
            cout << "Block number: " << number << endl;
            cout << "Previous Hash: " << prevHash << endl;
            cout << "Data: " << data << endl;
            cout << "Hash: " << hash << endl;
            cout << endl;
            cout << endl;
        }
        string hashFunc(){
            return sha256(to_string(number) + data + prevHash);
        }
};

class Blockchain {
    public:
        int lastBlock;
        Block block[10000];
        Blockchain(){
            block[0].setContent(0,"This is the first block", "0");
            lastBlock=0;
        }
        void newBlock(string data){
            lastBlock++;
            block[lastBlock].setContent(lastBlock, data, block[lastBlock-1].hash);
        }
        bool check(){
            for (int i=1; i<=lastBlock; i++){
                if (block[i].hash != block[i].hashFunc()){
                    return false;
                }
                else if (block[i].prevHash != block[i-1].hash){
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
    //myCoin.block[1].data="KEK";
    //myCoin.block[1].thisHash=myCoin.block[1].getHash();
    //myCoin.block[2].prevHash=myCoin.block[1].thisHash;
    //myCoin.block[2].thisHash=myCoin.block[2].getHash();
    if (myCoin.check())
        cout << "Blockchain is valid" << endl;
    else
        cout << "Blockchain is corrupted" << endl;
    return 0;
}
