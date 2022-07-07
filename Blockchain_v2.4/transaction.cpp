#include <iostream>
#include "transaction.h"
#include "sha256.h"
#include "signature.h"
using namespace std;

void Transaction::addData(int setNumber, string *setSender, string *setReceiver, int setValue){
    number=setNumber;
    sender=*setSender;
    receiver=*setReceiver;
    value=setValue;
}

void Transaction::sign(string *privKey){
    Signature sign;
    signature=sign.encrypt(hashFunc(), privKey);
    //cout << "SASAI" << endl;
    //cout << "TRANSACTION: SIGN " << signature << endl;

}
string Transaction::hashFunc(){
    return sha256(to_string(number) + sender + receiver + to_string(value));
}
