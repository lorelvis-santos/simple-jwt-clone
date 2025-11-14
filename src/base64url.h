#ifndef BASE64URL_H
#define BASE64URL_H

#include <string>

std::string base64url_encode(const std::string& input);
std::string base64url_decode(const std::string& input, bool debug = false);

#endif