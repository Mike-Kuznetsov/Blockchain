#ifndef MINER_H
#define MINER_H

#include <string>
#include "block.h"
#include "user.h"
#include "signature.h"
#include <thread>

class Miner {
    public:
        int minerID;
        std::string pubKey;
        std::string privKey;
        User *user;
        Miner *miner;
        std::string zeros;
        Block currentBlock;
        Block receivedBlock;
        bool blockAvailable = false;
        void sendBlock();
        void start(User *user1, Miner *miner, int ID);
        void addTransaction(Transaction *setTransaction);
        void mining(int difficulty);
        void setBlock(Block receivedBlock);
};

#endif
