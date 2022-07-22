#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        std::string zeros;
        int difficulty;
        int lastBlock;
        Block block[100];
        void start(int setDifficulty);
        void setBlock(Block receivedBlock);
        bool check();
        void showChain();
        void showData();
};
#endif
