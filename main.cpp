#include "src/base64.h"
#include <string>
#include <iostream>

int main() {
    std::cout << "base64 encoding: " << base64_encode("And") << std::endl;
    return 0;
}