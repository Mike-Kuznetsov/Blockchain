#ifndef USER_H
#define USER_H
#include "transaction.h"

class User {
    public:
        int id;
        int balances[10];
        Transaction transaction[100];
        std::string pubKey;
        std::string privKey;
};
#endif
