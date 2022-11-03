#ifndef MPAGS_RUNCAESARCIPHER_HPP
#define MPAGS_RUNCAESARCIPHER_HPP

#include <string>

std::string runCaesarCipher(
    const std::string& inputText,
    const size_t key,
    const bool encrypt
);

#endif