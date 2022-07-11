#include <iostream>
#include "transaction.h"
#include "sha256.h"
#include "signature.h"

using namespace std;

void Transaction::addData(int setNumber, string setSender, string setReceiver, int setValue){
    number=setNumber;
    sender=setSender;
    receiver=setReceiver;
    value=setValue;
}

string Transaction::hashFunc(){
    return sha256(to_string(number) + sender + receiver + to_string(value));
}

void Transaction::sign(string *privKey){
    signature=sig.encrypt(hashFunc(), privKey);
}

bool Transaction::check(){
    string str=sig.decrypt(&signature, &sender);
    if (str==hashFunc()){
        return true;
    }
    else{
        return false;
    }
}
