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
    std::size_t i = 0;
    std::size_t len = input.size();

    while (i + 3 <= len) {
        // We get three bytes from the input
        unsigned char byte0 = static_cast<unsigned char>(input[i]);
        unsigned char byte1 = static_cast<unsigned char>(input[i+1]);
        unsigned char byte2 = static_cast<unsigned char>(input[i+2]);

        i += 3;

        // We convert the three bytes (24 bits) into four sections of 6 bits (4x6 = 24 bits)
        unsigned int index0 = (byte0 & 0b11111100) >> 2;
        unsigned int index1 = ((byte0 & 0b00000011) << 4 | (byte1 >> 4));
        unsigned int index2 = ((byte1 & 0b00001111) << 2 | (byte2 >> 6));
        unsigned int index3 = ((byte2 & 0b00111111));

        // We use our base64 alphabet to get the letters for each index
        out.push_back(BASE64_ALPHABET[index0]);
        out.push_back(BASE64_ALPHABET[index1]);
        out.push_back(BASE64_ALPHABET[index2]);
        out.push_back(BASE64_ALPHABET[index3]);
    }

    // To do: fill remaining bits with = (this happens when there's bytes remaining from the input)
    std::size_t remaining = len - i;

    // Hay que recordar que base64 siempre produce 4 caracteres en base64

    // Caso 1
    // Nos queda 1 byte -> 8 bits
    // Podemos hacer 2 caracteres base64
    // Primeros 6 bits del byte
    // Ultimos 2 bits del byte + relleno de 4 bits con 0
    // Padding de caracteres con = 

    // Caso 2
    // Nos quedan 2 bytes -> 16 bits
    // Podemos hacer 3 caracteres
    // Primeros 6 bits del byte1
    // Ultimos 2 bits del byte1 + primeros 4 bits del byte2
    // Ultimos 4 bits del byte2 + relleno de 2 bits con 0

    if (remaining == 1) {
        unsigned char byte0 = static_cast<unsigned char>(input[i]);

        unsigned int index0 = (byte0 & 0b11111100) >> 2;
        unsigned int index1 = (byte0 & 0b00000011) << 4;

        out.push_back(BASE64_ALPHABET[index0]);
        out.push_back(BASE64_ALPHABET[index1]);
        out.push_back('=');
        out.push_back('=');
    } else if (remaining == 2) {
        unsigned char byte0 = static_cast<unsigned char>(input[i]);
        unsigned char byte1 = static_cast<unsigned char>(input[i+1]);

        unsigned int index0 = (byte0 & 0b11111100) >> 2;
        unsigned int index1 = ((byte0 & 0b00000011) << 4 | (byte1 >> 4));
        unsigned int index2 = (byte1 & 0b00001111) << 2;

        out.push_back(BASE64_ALPHABET[index0]);
        out.push_back(BASE64_ALPHABET[index1]);
        out.push_back(BASE64_ALPHABET[index2]);
        out.push_back('=');
    }

    return out;
}
