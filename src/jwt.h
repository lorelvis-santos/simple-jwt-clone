// src/jwt.h
#ifndef JWT_H
#define JWT_H

#include <string>

struct JwtHeader {
    std::string alg = "HS256";        // algoritmo por defecto
    std::string typ = "LORELVIS-JWT"; // tipo de token
};

struct JwtPayload {
    std::string id;
    std::string name;
};

std::string jwt_header_to_json(const JwtHeader& header);
std::string jwt_payload_to_json(const JwtPayload& payload);

#endif