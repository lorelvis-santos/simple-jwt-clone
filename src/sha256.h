#ifndef SHA256_H
#define SHA256_H

#include <array>
#include <string>

std::array<unsigned char, 32> sha256_bytes(const std::string& input);
std::string sha256_hex(const std::string& input);

#endif