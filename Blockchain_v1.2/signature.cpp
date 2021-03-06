#include <iostream>
#include "signature.h"
#include <memory>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <fstream>
extern "C"
{
#include <openssl/applink.c>
}
using namespace std;
using RSA_ptr = std::unique_ptr<RSA, decltype(&::RSA_free)>;
using BIO_MEM_ptr = std::unique_ptr<BIO, decltype(&::BIO_free)>;

string Signature::keyGen(){
    int rc = 0;
    unsigned long err = 0;
    RSA *rsa = RSA_new();
    BIO_MEM_ptr bioPriv(BIO_new(BIO_s_mem()), ::BIO_free);
     BIO_MEM_ptr bioPub(BIO_new(BIO_s_mem()), ::BIO_free);
    OpenSSL_add_all_ciphers();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);
    while (RAND_status() != 1) {
        RAND_seed(bne, 200);
    }
    RSA_generate_key_ex(rsa, 1024, bne, NULL);
    rc = PEM_write_bio_RSAPrivateKey(bioPriv.get(), rsa, NULL, NULL, NULL, NULL, NULL);
    rc = PEM_write_bio_RSAPublicKey(bioPub.get(), rsa);
    err = ERR_get_error();
    if (rc != 1)
    {
        cerr << "PEM_write_bio_RSA failed, error " << err << ", ";
        cerr << std::hex << "0x" << err;
        exit(1);
    }
    BUF_MEM *mem = NULL;
    BIO_get_mem_ptr(bioPriv.get(), &mem);
    err = ERR_get_error();
    if (!mem || !mem->data || !mem->length)
    {
        cerr << "BIO_get_mem_ptr failed, error " << err << ", ";
        cerr << std::hex << "0x" << err;
        exit(2);
    }
    string priv(mem->data, mem->length);
    //cout << privKey << endl;
    BIO_get_mem_ptr(bioPub.get(), &mem);
    err = ERR_get_error();
    if (!mem || !mem->data || !mem->length)
    {
        cerr << "BIO_get_mem_ptr failed, error " << err << ", ";
        cerr << std::hex << "0x" << err;
        exit(2);
    }
    string pub(mem->data, mem->length);
    pubKey=priv;
    return pub;
}

string Signature::encrypt(string input, string *privKey){
	BIO *bufio;
    RSA *rsa;
    bufio = BIO_new_mem_buf((*privKey).c_str(), 251); // (void*)
    RSA *myRSA = PEM_read_bio_RSAPublicKey(bufio, 0, 0, 0);
	OpenSSL_add_all_algorithms();
	unsigned char kekOutput[128];
	RSA_public_encrypt(117, (unsigned char*)input.c_str(), kekOutput, myRSA, RSA_PKCS1_PADDING);
    string str( kekOutput, kekOutput + 128 );
    return str;
}

string Signature::decrypt(string *input, string *pubKey2){
    unsigned char *input2 = (unsigned char *)(*input).c_str();
    unsigned char *rsaPrivateKeyChar = (unsigned char *)(*pubKey2).c_str();
    BIO *rsaPrivateBIO = BIO_new_mem_buf(rsaPrivateKeyChar, -1);
    RSA *pubKey3 = NULL;
	OpenSSL_add_all_algorithms();
	pubKey3 = PEM_read_bio_RSAPrivateKey(rsaPrivateBIO, NULL, 0, NULL);//(void *)"aaaaaaaaaaaaaaaa");
	unsigned char ptext[64];
	RSA_private_decrypt(128, input2, ptext, pubKey3, RSA_PKCS1_PADDING);
	string str(ptext, ptext + 64);
	return str;
}
