#ifndef MINER_H
#define MINER_H

#include <string>
#include "block.h"
#include "user.h"

class Miner {
    public:
        Miner();
        User *user = new User[4];
        //User *user;
        std::string zeros;
        Block currentBlock;
        void sendBlock();
        void start(User *user1);
        void addData(std::string newData);
        void mining(int difficulty);
};

#endif

