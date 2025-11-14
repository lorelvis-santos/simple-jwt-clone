#include "src/base64.h"
#include <string>
#include <iostream>

int main() {
    std::string input;

    std::cout << "input: ";
    std::getline(std::cin, input);

    std::cout << "base64 encoding: " << base64_encode(input) << std::endl;
    return 0;
}