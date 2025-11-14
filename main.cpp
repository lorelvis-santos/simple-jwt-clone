#include "src/base64.h"
#include <string>
#include <iostream>

int main() {
    std::string input;

    std::cout << "input: ";
    std::getline(std::cin, input);

    std::string encoded = base64_encode(input);

    std::cout << "base64 encoding: " << base64_encode(input) << std::endl;
    std::cout << "decoded string (base64): " << base64_decode(encoded) << std::endl;

    return 0;
}