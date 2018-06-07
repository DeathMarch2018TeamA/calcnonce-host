#ifndef SHA256_CALC_H
#define SHA256_CALC_H

#ifdef __cplusplus
extern "C" {
#endif

void hash_SHA256(const char *ZERO_SIZE,const char* BLOCK, char* nonce);

#ifdef __cplusplus
}
#endif

#endif   // SHA256_CALC_H
