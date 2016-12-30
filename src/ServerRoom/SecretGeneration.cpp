//
// Created by victor on 01/12/16.
//

#include "ServerRoom/SecretGeneration.hpp"

SecretGeneration::~SecretGeneration() {

}

SecretGeneration::SecretGeneration() {
    secretBase = 745; // Roberto toeic
}

unsigned int SecretGeneration::generateSecret() {
    ++secretBase;
    return secretBase;
}

template<>
SecretGeneration &Singleton<SecretGeneration>::Instance()
{
    static SecretGeneration _inst;

    return _inst;
}