#include <iostream>
#include <memory>
#include "signature.h"
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

unsigned char* Signature::encrypt(string input, string *privKey){
	BIO *bufio;
    RSA *rsa;
    unsigned int byteCount = 251;
    //cout << pubKey << endl;
    bufio = BIO_new_mem_buf((*privKey).c_str(), byteCount); // (void*)
    RSA *myRSA = PEM_read_bio_RSAPublicKey(bufio, 0, 0, 0);
	int outlen;
	OpenSSL_add_all_algorithms();
    unsigned char kekInput[117];
    for (int i=0; i<117; i++){
        kekInput[i]=static_cast<char>(80);
    }
    //cout << kekInput << endl;
	outlen = RSA_public_encrypt(117, (unsigned char*)input.c_str(), kekOutput, myRSA, RSA_PKCS1_PADDING);
    //cout << "kekOutput: " << kekOutput << endl;
    return kekOutput;
}

void Signature::decrypt(){
    ofstream out("public.key");
    out << pubKey;
    out.close();
	int outlen;
    RSA * pubKey2 = NULL;
	FILE * pubKey_file;
	unsigned char *ptext;
	OpenSSL_add_all_algorithms();
	pubKey_file = fopen("public.key", "rb");
	pubKey2 = PEM_read_RSAPrivateKey(pubKey_file, NULL, NULL, NULL);//(void *)"aaaaaaaaaaaaaaaa");
	outlen = RSA_private_decrypt(128, kekOutput, ptext, pubKey2, RSA_PKCS1_PADDING);
	cout << "OUTLEN KEK: " << outlen << endl;
	cout << "PTEXT: " << ptext << endl;
	cout << "File decrypted" << endl;
}
