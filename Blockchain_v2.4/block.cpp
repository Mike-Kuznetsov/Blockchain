#include <iostream>
#include "sha256.h"
#include "block.h"
#include "transaction.h"
#include "signature.h"

using namespace std;

void Block::setContent(int setNumber, string setPrevHash, int setBalances[9], int setTransCount[9], Signature *setSignature){
    prevHash=setPrevHash;
    number=setNumber;
    nonce=0;
    hash="";
    i=0;
    signature=setSignature;
    for (int j=0;j<9;j++){
        balances[j]=setBalances[j];
        transactionCount[j]=setTransCount[j];
    }
    //data="";
}

void Block::addTransaction(Transaction *transaction){
    //data+=newData;
    transactions[i]=*transaction;
    i++;
}

string Block::hashFunc(){
    return sha256(to_string(number) + data + prevHash + to_string(nonce));
}
