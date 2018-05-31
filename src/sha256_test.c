/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
	          implementation. These tests do not encompass the full
	          range of available test vectors, however, if the tests
	          pass it is very, very likely that the code is correct
	          and was compiled properly. This code also serves as
	          example usage of the functions.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include <stdlib.h>	//rand()

#include "sha256.h"

/*********************** FUNCTION DEFINITIONS ***********************/
int sha256_test()
{
	BYTE text1[] = {"abc"};

	BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
	                                 0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};

	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	int idx;
	int pass = 1;

	BYTE test[SHA256_BLOCK_SIZE];

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);

	printf("buf:%s\n",test);

	BYTE hash2[SHA256_BLOCK_SIZE] = {"ba78"};

/*
  	for(int i = 0; i < SHA256_BLOCK_SIZE; i++){
    	sprintf(test,"%02x", (unsigned char)buf[i]);
  	}
*/
	int cpylen=10;

	snprintf(test,cpylen+1,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		(unsigned char)buf[0],(unsigned char)buf[1],(unsigned char)buf[2],(unsigned char)buf[3],
		(unsigned char)buf[4],(unsigned char)buf[5],(unsigned char)buf[6],(unsigned char)buf[7],
		(unsigned char)buf[8],(unsigned char)buf[9],(unsigned char)buf[10],(unsigned char)buf[11],
		(unsigned char)buf[12],(unsigned char)buf[13],(unsigned char)buf[14],(unsigned char)buf[15],
		(unsigned char)buf[16],(unsigned char)buf[17],(unsigned char)buf[18],(unsigned char)buf[19],
		(unsigned char)buf[20],(unsigned char)buf[21],(unsigned char)buf[22],(unsigned char)buf[23],
		(unsigned char)buf[24],(unsigned char)buf[25],(unsigned char)buf[26],(unsigned char)buf[27],
		(unsigned char)buf[28],(unsigned char)buf[29],(unsigned char)buf[30],(unsigned char)buf[31]);
	


	printf("test:%s\n",test);

	if(!memcmp(hash2, buf, 2)) printf("test\n");

	pass = !memcmp(hash1, buf, SHA256_BLOCK_SIZE);


	return(pass);
}


void string_change(BYTE *hash, char *string_hash, int cpylen){

	snprintf(string_hash,cpylen+1,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		(unsigned char)hash[0],(unsigned char)hash[1],(unsigned char)hash[2],(unsigned char)hash[3],
		(unsigned char)hash[4],(unsigned char)hash[5],(unsigned char)hash[6],(unsigned char)hash[7],
		(unsigned char)hash[8],(unsigned char)hash[9],(unsigned char)hash[10],(unsigned char)hash[11],
		(unsigned char)hash[12],(unsigned char)hash[13],(unsigned char)hash[14],(unsigned char)hash[15],
		(unsigned char)hash[16],(unsigned char)hash[17],(unsigned char)hash[18],(unsigned char)hash[19],
		(unsigned char)hash[20],(unsigned char)hash[21],(unsigned char)hash[22],(unsigned char)hash[23],
		(unsigned char)hash[24],(unsigned char)hash[25],(unsigned char)hash[26],(unsigned char)hash[27],
		(unsigned char)hash[28],(unsigned char)hash[29],(unsigned char)hash[30],(unsigned char)hash[31]);

}

void random_nonce(char *nonce){

	const char set[] = "0123456789abcdef";
	int randam;

	for(int i = 0; i < strlen(nonce); i++){
		randam = rand() % 16;
		nonce[i]= set[randam];
	}

}

void hash_SHA256(char *ZERO_SIZE,char* BLOCK,char* nonce){


	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	BYTE blocknonce[100];

	random_nonce(nonce);

	strcpy(blocknonce,BLOCK);
	strcat(blocknonce,nonce);

	printf("blocknonce:%s\n",blocknonce);

	sha256_init(&ctx);
	sha256_update(&ctx, blocknonce, strlen(blocknonce));
	sha256_final(&ctx, buf);

	char hash[100];
	string_change(buf,hash,80);

	printf("hash:%s\n",hash);


}

void calc_nonce(char* ZERO_SIZE,char* BLOCK){

	char nonce[9]="aaaaaaaa";
	

	hash_SHA256(ZERO_SIZE,BLOCK,nonce);

	printf("nonce:%s\n",nonce);
}


/*
string *calc_nonce(string *zero_size, string *block){
	//initial value
	string hash;
	string *nonce;
    string chain_block;
    nonce = new string(8, ' ');

    do{
		random_nonce(nonce);
        chain_block = *block + *nonce;
		hash = hash_sha256(&chain_block);
    }while(!(hash->substr(0, zero->size()) == *zero));

	return nonce;
}

string hash_sha256(string *block_nonce){
	string hash_1st, hash_2nd;

   	hash_1st = picosha2::hash256_hex_string(*block_nonce);
	hash_2nd = picosha2::hash256_hex_string(hash_1st);

	return hash_2nd;
}



*/


int main()
{
	char ZERO[]="00000";
	char BLOCK[]="aaaaaaaaaa";

	srand(0);

	calc_nonce(ZERO,BLOCK);


	//printf("SHA-256 tests: %s\n", sha256_test() ? "SUCCEEDED" : "FAILED");

	return(0);
}
