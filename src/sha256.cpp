#include "sha256.h"

#include <cstdint>
#include <vector>
#include <sstream>
#include <iomanip>

namespace {

// ---------- Helper functions ----------

constexpr std::uint32_t rotr(std::uint32_t x, std::uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

constexpr std::uint32_t ch(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
    return (x & y) ^ (~x & z);
}

constexpr std::uint32_t maj(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

constexpr std::uint32_t big_sigma0(std::uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

constexpr std::uint32_t big_sigma1(std::uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

constexpr std::uint32_t small_sigma0(std::uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

constexpr std::uint32_t small_sigma1(std::uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

// SHA-256 constants K[0..63]
constexpr std::uint32_t K[64] = {
    0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,
    0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
    0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,
    0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
    0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,
    0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
    0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,
    0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
    0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,
    0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
    0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,
    0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
    0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,
    0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
    0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,
    0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
};

} // anonymous namespace

// ---------- Public functions ----------

std::array<unsigned char, 32> sha256_bytes(const std::string& input) {
    // Initial hash values H0..H7 (first 32 bits of fractional parts of sqrt of primes)
    std::uint32_t H[8] = {
        0x6a09e667u,
        0xbb67ae85u,
        0x3c6ef372u,
        0xa54ff53au,
        0x510e527fu,
        0x9b05688cu,
        0x1f83d9abu,
        0x5be0cd19u
    };

    // Convert input to a mutable byte vector
    std::vector<unsigned char> msg(input.begin(), input.end());

    // Message length in bits (before padding)
    std::uint64_t bit_len = static_cast<std::uint64_t>(msg.size()) * 8u;

    // Padding: append 0x80, then 0x00 until length ≡ 56 mod 64
    msg.push_back(0x80u);
    while ((msg.size() % 64) != 56) {
        msg.push_back(0x00u);
    }

    // Append original length in bits as 64-bit big-endian
    for (int i = 7; i >= 0; --i) {
        msg.push_back(static_cast<unsigned char>((bit_len >> (i * 8)) & 0xFFu));
    }

    std::uint32_t W[64];

    // Process each 512-bit block (64 bytes)
    for (std::size_t offset = 0; offset < msg.size(); offset += 64) {
        // Break chunk into 16 big-endian 32-bit words W[0..15]
        for (int t = 0; t < 16; ++t) {
            std::size_t i = offset + t * 4;
            W[t] = (static_cast<std::uint32_t>(msg[i])     << 24) |
                   (static_cast<std::uint32_t>(msg[i + 1]) << 16) |
                   (static_cast<std::uint32_t>(msg[i + 2]) << 8)  |
                   (static_cast<std::uint32_t>(msg[i + 3]));
        }

        // Extend to W[16..63]
        for (int t = 16; t < 64; ++t) {
            W[t] = small_sigma1(W[t - 2]) + W[t - 7] + small_sigma0(W[t - 15]) + W[t - 16];
        }

        // Initialize working variables a..h
        std::uint32_t a = H[0];
        std::uint32_t b = H[1];
        std::uint32_t c = H[2];
        std::uint32_t d = H[3];
        std::uint32_t e = H[4];
        std::uint32_t f = H[5];
        std::uint32_t g = H[6];
        std::uint32_t h = H[7];

        // Main compression loop
        for (int t = 0; t < 64; ++t) {
            std::uint32_t T1 = h + big_sigma1(e) + ch(e, f, g) + K[t] + W[t];
            std::uint32_t T2 = big_sigma0(a) + maj(a, b, c);

            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // Add compressed chunk to current hash value
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }

    // Produce final hash as 32 bytes (big-endian)
    std::array<unsigned char, 32> out{};
    for (int i = 0; i < 8; ++i) {
        out[i * 4 + 0] = static_cast<unsigned char>((H[i] >> 24) & 0xFFu);
        out[i * 4 + 1] = static_cast<unsigned char>((H[i] >> 16) & 0xFFu);
        out[i * 4 + 2] = static_cast<unsigned char>((H[i] >> 8)  & 0xFFu);
        out[i * 4 + 3] = static_cast<unsigned char>((H[i])       & 0xFFu);
    }

    return out;
}

std::string sha256_hex(const std::string& input) {
    auto bytes = sha256_bytes(input);
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (unsigned char b : bytes) {
        oss << std::setw(2) << static_cast<int>(b);
    }
    return oss.str();
}
