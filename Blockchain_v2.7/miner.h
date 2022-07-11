#ifndef MINER_H
#define MINER_H

#include <string>
#include "block.h"
#include "user.h"
#include "signature.h"
#include <mutex>
#include <thread>
class Miner {
    public:
        std::string pubKey;
        std::string privKey;
        void start(User *user1, Miner *miner1, int ID, std::mutex *setMtx);
        void addTransaction(Transaction *setTransaction);
        void setBlock(Block receivedBlock);
        Block currentBlock;
    private:
        User *user;
        Miner *miner;
        std::mutex *mtx;
        int oldBalances[8];
        int minerID;
        std::string zeros;
        Block receivedBlock;
        bool blockAvailable = false;
        void sendBlock();
        void mining(int difficulty);
};

#endif
