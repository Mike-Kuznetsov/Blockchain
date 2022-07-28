#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        User();
        int lastBlock;
        Block block[100];
        void start(int ID, int setDifficulty, User *user, std::string *pubKeys);
        std::string privKey;
        std::string pubKey;
        void setBlock(Block receivedBlock);
        bool check();
        void showChain();
    private:
        int balances[8];
        std::string *pubKeys;
        std::string zeros;
        bool checkBlock(Block *receivedBlock);
        bool checkTransactions(Block *receivedBlock);
        int difficulty;
        User *user;
        int myID;
};
#endif
