#include <iostream>
#include "sha256.h"
#include "block.h"
#include "transaction.h"

using namespace std;

void Block::setContent(int setNumber, string setPrevHash, int setBalances[9], int setTransCount[9]){
    prevHash=setPrevHash;
    number=setNumber;
    nonce=0;
    hash="";
    i=0;
    for (int i=0;i<9;i++){
        balances[i]=setBalances[i];
        transactionCount[i]=setTransCount[i];
    }
    //data="";
}

void Block::addTransaction(Transaction transaction){
    //data+=newData;
    transactions[i]=transaction;
    i++;
}

string Block::hashFunc(){
    return sha256(to_string(number) + data + prevHash + to_string(nonce));
}
