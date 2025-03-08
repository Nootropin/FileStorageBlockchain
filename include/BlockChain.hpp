#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP
#include "Block.hpp"
#include <fstream>
#include <stdexcept>
class BlockChain{
    public:
        bool addBlock(const Block block);
        long long getLength() const;
        Block getBlock(const long long& id) const;
        const std::vector<Block>& getList() const;
        std::vector<unsigned char> getLastHash() const;
        BlockChain(Block block);
        BlockChain();
        std::vector<unsigned char> binarySerialize() const;
    private:
        long long _length;
        std::vector<unsigned char> _lastHash;
        std::vector<Block> _blockVector;
};
#endif