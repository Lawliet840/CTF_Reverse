#include <iostream>
#include <cstdint>
#include <iomanip>

uint32_t derive_key(uint32_t acc) {
    uint32_t key = acc;
    key ^= 0xDEADBEEF;
    key = (key << 7) | (key >> 25);
    key ^= 0xCAFEBABE;
    return key;
}

int main() {
    const char flag[] = "nucleaire";
    const size_t len = sizeof(flag) - 1;
    uint32_t acc = 77256;
    uint32_t key = derive_key(acc);
    std::cout << "uint8_t encrypted_flag[] = {\n    ";
    for (size_t i = 0; i < len; i++) {
        uint8_t k =((key >> ((i % 4) * 8)) & 0xFF)^ (0xA5 + i * 13);
        uint8_t enc = flag[i] ^ k;
        std::cout << "0x"
                  << std::hex << std::uppercase
                  << std::setw(2) << std::setfill('0')
                  << (int)enc;

        if (i + 1 < len)
            std::cout << ", ";
    }
    std::cout << "\n};\n";
    return 0;
}
