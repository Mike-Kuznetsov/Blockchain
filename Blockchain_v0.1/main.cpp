/* 
*   Blockchain for Mautoz Tech Youtube Video.
*   Version 0.1.
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
            hash=sha256(to_string(number) + data + prevHash);
            cout << "Block number: " << number << endl;
            cout << "Previous Hash: " << prevHash << endl;
            cout << "Data: " << data << endl;
            cout << "Hash: " << hash << endl;
            cout << endl;
            cout << endl;
        }

};

int main(int argc, char *argv[])
{
    Block block[10];
    block[0].setContent(0,"ABCD","0");
    block[1].setContent(1,"ABCDEFG",block[0].hash);
    block[2].setContent(2,"XYZ",block[1].hash);
    return 0;
}
