#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include<string>
#include"BlockChain.hpp"
#include"Hash.hpp"
struct Deserializer{
    BlockChain deserialize(std::vector<unsigned char> vInput, const SHA_256_HASHER* hash) const;
};
#endif