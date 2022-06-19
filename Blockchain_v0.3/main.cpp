/* 
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 0.3. Added proof of work and mining. Still no users and transactions.
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
#include <thread>
using namespace std;

class Block {
    public:
        int number;
        string hash;
        string prevHash;
        string data;
        int nonce;
        void createBlock(int setNumber, string setPrevHash){
            prevHash=setPrevHash;
            number=setNumber;
            nonce=0;
            hash="0";
            //cout << "Block number: " << number << endl;
            //cout << "Previous Hash: " << prevHash << endl;
            //cout << endl;
            //cout << endl;
        }
        void addData(string newData){
            data+=newData;
            //cout << "Data: " << data << endl;
        }
        string hashFunc(){
            return sha256(to_string(number) + data + prevHash + to_string(nonce));
        }

};

class Blockchain {
    public:
        int lastBlock;
        string data;
        string zeros;
        Block block[10000];
        Blockchain(){
            block[0].createBlock(0,"0");
            lastBlock=0;
            zeros="000000000000000000000000000000";
            thread thr(mining, this, 5);
            thr.detach();
        }
        void newBlock(){
            lastBlock++;
            block[lastBlock].createBlock(lastBlock, block[lastBlock-1].hash);
            zeros="000000000000000000000000000000";

        }
        void addData(string newData){
            block[lastBlock].addData(newData);
        }
        bool check(){
            for (int i=1; i<lastBlock; i++){
                if (block[i].hash != block[i].hashFunc()){
                    return false;
                }
                else if (block[i].prevHash != block[i-1].hash){
                    return false;
                }
            }
            return true;
        }
        void mining(int difficulty){
            while(true){
                zeros=zeros.substr(0, difficulty);
                while (block[lastBlock].hashFunc().substr(0, difficulty)!=zeros){
                    block[lastBlock].nonce++;
                }
                block[lastBlock].hash=block[lastBlock].hashFunc();
                //cout << "Block has been found" << endl;
                //cout << "HASH: " << block[lastBlock].hash << endl;
                newBlock();
            }
        }
        void showChain(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].prevHash << endl;
                cout <<  block[i].hash << endl;
            }
        }
        void showData(){
            for (int i; i<=lastBlock; i++){
                cout << "Block: " << i << endl;
                cout <<  block[i].data << endl;
            }
        }
};
int main(int argc, char *argv[])
{
    Blockchain myCoin;
    string input;
    while(true){
         cin >> input;
         if (input=="showData"){
            myCoin.showData();
         }
         else if (input=="showChain"){
            myCoin.showChain();
         }
         else if (input=="check"){
            if (myCoin.check())
                cout << "Blockchain is valid" << endl;
            else
                cout << "Blockchain is corrupted" << endl;
            }
         else{
            myCoin.addData(input);
         }
    }
    return 0;
}
