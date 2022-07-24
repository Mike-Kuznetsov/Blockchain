#ifndef MINER_H
#define MINER_H

#include <string>
#include <mutex>
#include "block.h"
#include "user.h"

class Miner {
    public:
        bool blockReceived = false;
        bool blockAvailable = false;
        bool minerStopped = false;
        Block newReceivedBlock;
        std::mutex *mtx;
        User *user;
        Miner *miner;
        int myID;
        std::string zeros;
        int difficulty;
        Block block[1000];
        int lastBlock;
        void setBlock(Block receivedBlock);
        bool checkBlock(Block *receivedBlock);
        void sendBlock();
        void start(User *setUser, std::mutex *setMtx, int setDifficulty, Miner *setMiner, int ID);
        void addData(std::string newData);
        void mining();
        bool check();
        void showData();
        void showChain();
};

#endif
