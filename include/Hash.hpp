#ifndef HASH_HPP
#define HASH_HPP
#include<vector>
#include<string>
#include<openssl/sha.h>
struct SHA_256_HASHER{
    SHA_256_HASHER(){}
    std::vector<unsigned char> hash(const std::vector<unsigned char>& input) const;
    std::string hashToHex(const std::vector<unsigned char>& input) const;
    const unsigned char hashSize = 32;
};
#endif // HASH_HPP