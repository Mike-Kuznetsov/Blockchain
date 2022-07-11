#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"
//#include "miner.h"

class User {
    public:
        int lastBlock;
        int userID;
        Block block[10000];
        User();
        void init(std::string *setPubKeys, int ID);
        std::string *pubKeys;
        std::string privKey;
        std::string pubKey;
        void setBlock(Block receivedBlock);
};
#endif
