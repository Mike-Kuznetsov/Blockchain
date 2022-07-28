#ifndef MINER_H
#define MINER_H

#include <string>
#include "block.h"
#include "transaction.h"
#include "user.h"
#include <mutex>

class Miner {
    public:
        Miner();
        Block block[100];
        std::string pubKey;
        std::string privKey;
        void start(User *user1, Miner *miner1, int ID, std::mutex *setMtx, int setDifficulty, std::string *pubKeys);
        void addTransaction(Transaction *setTransaction);
        void setBlock(Block receivedBlock);
        bool check();
        void showChain();
        int lastBlock;
    private:
        std::string *pubKeys;
        int balances[8];
        int difficulty;
        bool checkTransactions(Block *receivedBlock);
        bool checkBlock(Block *receivedBlock);
        bool blockReceived = false;
        bool blockAvailable = false;
        bool minerStopped = false;
        User *user;
        Miner *miner;
        std::mutex *mtx;
        int myID;
        std::string zeros;
        void sendBlock();
        void mining();
};

#endif
