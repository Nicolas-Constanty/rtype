//
// Created by victor on 01/12/16.
//

#ifndef RTYPE_SECRETGENERATION_HPP
#define RTYPE_SECRETGENERATION_HPP

#include <Common/Singleton.hpp>

class SecretGeneration : public Singleton<SecretGeneration> {
public:
    friend class Singleton<SecretGeneration>;

private:
    SecretGeneration();
    ~SecretGeneration();

public:
    unsigned int generateSecret();

private:
    unsigned int secretBase;
};

template class Singleton<SecretGeneration>;

#endif //RTYPE_SECRETGENERATION_HPP
