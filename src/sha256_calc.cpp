#include "sha256_calc.hpp"

#include <iostream>

#include <cstring>
#include <cstdlib>	//rand()

extern "C" {

#include "crypto-algorithms/sha256.h"

}

namespace  {
    
const int MY_HASH_SIZE = 64;

} // namespace 

namespace  {

void string_change(const BYTE *hash, char *string_hash, int cpylen){
    for (int i = 0; i < MY_HASH_SIZE / 2; i++) {
        snprintf(&(string_hash[i * 2]), 1, "%02x", (unsigned char)hash[i]);
    }
}

void random_nonce(char *nonce){
	const char set[] = "0123456789abcdef";

	for(int i = 0; i < strlen(nonce); i++){
		int randam = rand() % 16;
		nonce[i]= set[randam];
	}
}

void calc_SHA256(BYTE *data, char *hash, int hashlen){
    BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	
	sha256_init(&ctx);
	sha256_update(&ctx, data, sizeof(data) / sizeof(data[0]));
	sha256_final(&ctx, buf);

	string_change(buf, hash, MY_HASH_SIZE);

	sha256_init(&ctx); 
	sha256_update(&ctx, (BYTE *)hash, strlen(hash));
	sha256_final(&ctx, buf);

	string_change(buf, hash, hashlen);
}

bool countZero(const char *target, int num) {
    for (int i = 0; i < num; i++) {
        if (target[i] != '0') {
            return false;
        }
    }
    return true;
}

} // namespace 

namespace shigeCoin {

void hash_SHA256(const std::string ZERO_SIZE, const std::string BLOCK, char *nonce){
	BYTE *blocknonce;
	char *c_blocknonce;
	char hash[MY_HASH_SIZE+1];

	do {
	    random_nonce(nonce);
	    strcpy(c_blocknonce, BLOCK.c_str());
	    strcat(c_blocknonce, nonce);

	    blocknonce = (BYTE *) c_blocknonce;
	    calc_SHA256(blocknonce, hash, ZERO_SIZE.length());
	} while(countZero(hash, ZERO_SIZE.length()));

	//for debug
    std::cout << "blocknonce: " << *blocknonce << std::endl;
}

} // namespace shigeCoin
