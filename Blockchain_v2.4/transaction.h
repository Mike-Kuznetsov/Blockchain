#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction {
    public:
        int number;
        std::string receiver;
        std::string sender;
        int value;
        std::string signature;
        void addData(int setNumber, std::string *setSender, std::string *setReceiver, int setValue);
        void sign(std::string *privKey);
        std::string hashFunc();
};
#endif
