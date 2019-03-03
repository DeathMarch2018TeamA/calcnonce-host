#include "calc_nonce.hpp"

#include "sha256_calc.hpp"

namespace shigeCoin {

const std::string calc_nonce(const std::string zero_size, const std::string block) {
    char nonce_buf[9] = "00000000";
	hash_SHA256(zero_size, block, nonce_buf);
	return std::string(nonce_buf);
}

} // namespace shigeCoin
