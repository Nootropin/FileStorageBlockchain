#ifndef BLOCKCHAINALGO_HPP
#define BLOCKCHAINALGO_HPP
#include <vector>
#include "BlockChain.hpp"
#include "Transaction.hpp"
#include "File.hpp"
class BlockChainAlgo{
    public:
        BlockChainAlgo(SHA_256_HASHER* hash,BlockChain* blockchain){
            this->hash = hash;
            this->blockchain = blockchain;
        }
        std::vector<unsigned char> getFileLastHash(const std::vector<unsigned char> fileNameHash) const;
        std::vector<std::vector<unsigned char>> getFileHashes(const std::vector<unsigned char> fileNameHash) const;
        int addFileToBlock(std::string fileName);
        int createNewBlock();
        std::string getBlockSerialized(int id) const;
        int saveBlockchain(std::string outputFileName) const;
        
    private:
        SHA_256_HASHER* hash;
        BlockChain* blockchain;
        std::vector<Transaction> vBuffer;
};
#endif