#include <string>
#include <iostream>
#include "src/base64.h"
#include "src/jwt.h"

int main() {
    // std::string input;

    // std::cout << "input: ";
    // std::getline(std::cin, input);

    // std::string encoded = base64_encode(input);

    // std::cout << "base64 encoding: " << base64_encode(input) << std::endl;
    // std::cout << "decoded string (base64): " << base64_decode(encoded, false) << std::endl;

    JwtHeader header;
    JwtPayload payload;

    payload.id = "1";
    payload.name = "Lorelvis";

    std::cout << jwt_header_to_json(header) << std::endl;
    std::cout << jwt_payload_to_json(payload) << std::endl;

    return 0;
}