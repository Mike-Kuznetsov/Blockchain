#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "signature.h"
class Transaction {
    public:
        int number;
        std::string receiver;
        std::string sender;
        Signature sig;
        int value;
        std::string signature;
        void addData(int setNumber, std::string setSender, std::string setReceiver, int setValue);
        void sign(std::string *privKey);
        std::string hashFunc();
        bool check();
};
#endif
