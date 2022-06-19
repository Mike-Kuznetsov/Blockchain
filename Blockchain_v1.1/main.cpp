#include <iostream>
#include "miner.cpp"

using namespace std;

/*class User {
    public:
        int k=0;
        void setUsers(this setUser1, User setUser2, User setUser3){
            user=setUser1;
            user=setUser1;
            user=setUser1;
            k=1;
        }

};*/

/*class Transaction {
    public:
        int number, value;
        string sender, receiver, sign;
};*/

int main(int argc, char *argv[])
{
    User user1;
    Miner miner1;
    miner1.start(&user1);
    //user1.setMiners(miner1);
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
    //myCoin.block[1].data="KEK";
    //myCoin.block[1].thisHash=myCoin.block[1].getHash();
    //myCoin.block[2].prevHash=myCoin.block[1].thisHash;
    //myCoin.block[2].thisHash=myCoin.block[2].getHash();
    //cout << "kek";
    return 0;
}
