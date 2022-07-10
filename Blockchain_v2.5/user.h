#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        int lastBlock;
        Block block[10000];
        User();
        std::string privKey;
        std::string pubKey;
        void setBlock(Block receivedBlock);
};
#endif
