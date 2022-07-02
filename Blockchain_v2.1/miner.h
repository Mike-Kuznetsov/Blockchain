#ifndef MINER_H
#define MINER_H

#include <string>
#include "block.h"
#include "user.h"
#include "signature.h"
#include <thread>

class Miner {
    public:
        Miner();
        int minerID;
        std::string *privKey;
        User *user;// = new User[4];
        Miner *miner;// = new Miner[4];
        Signature *signature;
        std::string zeros;
        Block currentBlock;
        Block receivedBlock;
        bool blockAvailable = false;
        void sendBlock();
        void start(User *user1, Miner *miner, int ID, Signature *ptr, std::string *setPrivKey);
        void addData(std::string newData);
        void mining(int difficulty);
        void setBlock(Block receivedBlock);
};

#endif
