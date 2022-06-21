#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        int lastBlock;
        Block block[10000];
        User();
        void setBlock(Block receivedBlock);
        //void setMiners(Miner miner1);
        //void addData(std::string newData);
        bool check();
        void showChain();
        void showData();
};
#endif
