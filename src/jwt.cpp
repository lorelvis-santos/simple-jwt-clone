#include "jwt.h"

std::string jwt_header_to_json(const JwtHeader& header) {
    return "{\"alg\":\"" + header.alg + "\",\"typ\":\"" + header.typ + "\"}";;
}

std::string jwt_payload_to_json(const JwtPayload& payload) {
    return std::string("{\"id\":\"") + payload.id + "\",\"name\":\"" + payload.name + "\"}";
}
