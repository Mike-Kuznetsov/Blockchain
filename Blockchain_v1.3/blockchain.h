#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include "block.h"

class Blockchain {
    public:
        int lastBlock;
        std::string zeros;
        Block block[10000];
        Blockchain();
        void newBlock();
        void addData(std::string newData);
        bool check();
        void mining(int difficulty);
        void showChain();
        void showData();
};
#endif
