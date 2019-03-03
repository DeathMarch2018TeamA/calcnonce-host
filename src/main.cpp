#include <array>
#include <iostream>	// cout
#include <string>	// string

#include <cstdlib>	// rand,srand

#include "calc_nonce.hpp"
#include "comm.hpp"

using namespace shigeCoin;

int main(int argc, const char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [IP_address] [port]";
        return 1;
    }

    std::string team_name = "shigeCoin";
    std::string zero_num;
    std::array<std::string, 10> block, nonce;

    // seed set for randam_nonce()
    srand((unsigned)time(NULL));
    
    // sign up for server
    if (!initialize(team_name, argv[1], argv[2])) {
        std::cout << "failed to initialize socket" << std::endl;
        return 2;
    }

    zero_num = get_zero();
    std::cout << "zero_num: " << zero_num << std::endl;

    // calculate nonce
    for (int i = 0; i < 10; i++) {
        block[i] = get_block();
        nonce[i] = calc_nonce(zero_num, block[i]);

        if (!send_nonce(nonce[i])) {
            std::cout << "failed to send nonce" << std::endl;
            return 3;
        }

        std::cout << "block: " << block[i] << std::endl;
        std::cout << "nonce: " << nonce[i] << std::endl;
    }

    if (!finalize()) {
        std::cout << "failed to finalize socket" << std::endl;
    }

    return 0;
}
