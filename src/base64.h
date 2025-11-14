#ifndef BASE64_H
#define BASE64_H

#include <string>

std::string base64_encode(const std::string& input);
std::string base64_decode(const std::string& input, bool debug = false);

#endif