#ifndef SHA256_CALC_HPP
#define SHA256_CALC_HPP

#include <string>

namespace shigeCoin {

void hash_SHA256(const std::string ZERO_SIZE, const std::string BLOCK, char *nonce);

} // namespace shigeCoin

#endif   // SHA256_CALC_HPP
