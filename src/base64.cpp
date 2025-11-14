#include "base64.h"
#include <string>
#include <vector>

// Tenemos un diccionario de 64 carácteres
// [A-z][a-z][0-9][+/]

// Tomamos una entrada, por cada 3 bytes lo convertimos
// en 4 bloques de 6 bits y usamos nuestro diccionario para producir
// nuestra nueva salida

static const std::string BASE64_ALPHABET = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/";

std::string base64_encode(const std::string& input) {
    std::string out;

    // 128 64  32  16  8   4   2   1
    // 0   0   0   0   0   0   0   0

    // A -> 65  -> 0100 0001
    // n -> 110 -> 0110 1110
    // d -> 100 -> 0110 0100

    // 32  16  8  |  4   2   1
    // 0   0   0  |  0   0   0

    // i1 -> 010 000 -> 16 -> Q
    // i2 -> 010 110 -> 22 -> W
    // i3 -> 111 001 -> 57 -> 5
    // i4 -> 100 100 -> 36 -> k

    std::string str = "And";

    unsigned char byte0 = str[0];
    unsigned char byte1 = str[1];
    unsigned char byte2 = str[2];

    unsigned int index0 = (byte0 & 0b11111100) >> 2;
    // Mask structure, not real values.
    // ((byte0 & 0b00000011) << 4) -> 00110000
    // (byte1 >> 4)                -> 00001111
    // | operand with 2 values     -> 00111111
    unsigned int index1 = ((byte0 & 0b00000011) << 4 | (byte1 >> 4));
    unsigned int index2 = ((byte1 & 0b00001111) << 2 | (byte2 >> 6));
    unsigned int index3 = ((byte2 & 0b00111111));

    out.push_back(BASE64_ALPHABET[index0]);
    out.push_back(BASE64_ALPHABET[index1]);
    out.push_back(BASE64_ALPHABET[index2]);
    out.push_back(BASE64_ALPHABET[index3]);

    return out;
}
