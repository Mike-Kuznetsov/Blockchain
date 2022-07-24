#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        std::string zeros;
        User *user;
        int myID;
        int difficulty;
        int lastBlock;
        Block block[1000];
        void start(int setDifficulty, int ID, User *user);
        void setBlock(Block receivedBlock);
        bool check();
        void showChain();
        void showData();
        bool checkBlock(Block *receivedBlock);
};
#endif
