#include <algorithm>
#include "base64.h"
#include "base64url.h"

std::string base64url_encode(const std::string& input) {
    std::string b64 = base64_encode(input);

    // replace + -> -
    std::replace(b64.begin(), b64.end(), '+', '-');

    // replace / -> _
    std::replace(b64.begin(), b64.end(), '/', '_');

    // remove '=' padding
    while (!b64.empty() && b64.back() == '=') {
        b64.pop_back();
    }

    return b64;
}

std::string base64url_decode(const std::string& input, bool debug) {
    std::string b64 = input;

    std::replace(b64.begin(), b64.end(), '-', '+');
    std::replace(b64.begin(), b64.end(), '_', '/');

    // restore padding to multiple of 4
    while (b64.size() % 4 != 0) {
        b64.push_back('=');
    }

    return base64_decode(b64, false);
}