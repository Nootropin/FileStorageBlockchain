#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <chrono>
#include <vector>
#include <cstring> 
#include "Hash.hpp"
#include "Transaction.hpp"

struct Block{
    const std::vector<unsigned char> previousBlockHash;
    const long long id;
    const time_t timestamp;
    std::vector<Transaction> transactions;
    const SHA_256_HASHER* hasher;
    std::vector<unsigned char> binarySerialize() const;
    std::string humanReadableFormat() const;
    std::vector<unsigned char> blockHash;
    Block(const std::vector<unsigned char>& previousBlockHash, const long long& id, const time_t& timestamp, const std::vector<Transaction>& transactions, const SHA_256_HASHER* hasher);
};

#endif // BLOCK_HPP