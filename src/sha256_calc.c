#include <stdio.h> 
#include <string.h>
#include <stdlib.h>	//rand()

#include "crypto-algorithms/sha256.h"
#include "sha256_calc.h"

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

void calc_SHA256(BYTE data[], char *hash, int hashlen){
        BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	
	sha256_init(&ctx);
	sha256_update(&ctx, data, sizeof(data) / sizeof(data[0]));
	sha256_final(&ctx, buf);

	string_change(buf, hash, 64);

	sha256_init(&ctx); 
	sha256_update(&ctx, (BYTE *)hash, strlen(hash));
	sha256_final(&ctx, buf);

	string_change(buf, hash, hashlen);
}

void hash_SHA256(const char *ZERO_SIZE, const char* BLOCK, char* nonce){

	BYTE *blocknonce;
	char *c_blocknonce;
	char hash[65];

	do{
	random_nonce(nonce);

	strcpy(c_blocknonce, BLOCK);
	strcat(c_blocknonce, nonce);

	blocknonce = (BYTE *) c_blocknonce;
	calc_SHA256(blocknonce, hash, strlen(ZERO_SIZE));

	} while(strcmp(hash, ZERO_SIZE));

	//for debug
	printf("blocknonce:%s\n", *blocknonce);

}

