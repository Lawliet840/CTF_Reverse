#include <iostream>
#include <cstdint>

// dérivation de clé : déterministe et unique
uint32_t derive_key(uint32_t acc) {
    uint32_t key = acc;
    key ^= 0xDEADBEEF;
    key = (key << 7) | (key >> 25);   // rotation gauche
    key ^= 0xCAFEBABE;
    return key;
}

void decrypt_flag(uint32_t key) {
    uint8_t encrypted_flag[] = {
        0x9A, 0xEE, 0x6B, 0x3C, 0xED, 0xAE, 0x2D, 0xEE, 0x39
    };

    const size_t len = sizeof(encrypted_flag);

    for (size_t i = 0; i < len; i++) {
        uint8_t k =
            ((key >> ((i % 4) * 8)) & 0xFF)
            ^ (0xA5 + i * 13);   // diffusion
        encrypted_flag[i] ^= k;
    }

    std::cout << "FLAG{";
    for (size_t i = 0; i < len; i++)
        std::cout << encrypted_flag[i];
    std::cout << "}" << std::endl;
}


int main() {
    int dose[5];
    for (int i = 0; i < 5; i++) {
        std::cin >> dose[i];
    }

    const uint32_t weight[5] = {173, 91, 47, 201, 59};
    const uint32_t salt[5]   = {0x12, 0x34, 0x56, 0x78, 0x9A};
    const uint8_t  shift[5]  = {1, 2, 1, 3, 2};

    uint32_t acc = 0;

    for (int i = 0; i < 5; i++) {
        acc += ((dose[i] ^ salt[i]) * weight[i]) >> shift[i];
    }

    acc = (acc + 0x238) % 100000;
    if ((((acc - 10615) ^ 0xBEEF) & 0xFFFF) == 0xBABE) {
        uint32_t key = derive_key(acc);
        decrypt_flag(key);
    } else {
        std::cout << "Radiation level: " << acc << std::endl;
    }

    return 0;
}
