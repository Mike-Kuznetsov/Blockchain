#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        int lastBlock;
        Block block[10000];
        User();
        std::string *privKey;
        void setPrivKey(std::string *setPrivKey);
        void setBlock(Block receivedBlock);
        //void addData(std::string newData);
};
#endif
