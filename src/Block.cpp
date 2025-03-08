#include "Block.hpp"
Block::Block(const std::vector<unsigned char>& previousBlockHash,const long long& id,const time_t& timestamp,const std::vector<Transaction>& transactions,const SHA_256_HASHER* hasher):previousBlockHash(previousBlockHash),id(id),timestamp(timestamp),transactions(transactions){
    long long blockSize = 0;
    blockSize += previousBlockHash.size();
    blockSize += sizeof(id);
    blockSize += sizeof(timestamp);
    for(auto& i:transactions){
        blockSize += i.size();
    }
    std::vector<unsigned char> concBlock = binarySerialize();
    std::vector<unsigned char> blockH = hasher->hash(concBlock);
    this->blockHash = blockH;
}
// 32 bytes of previous hash
// 8 bytes of long long 
// 8 bytes of time creation
// 4 bytes of transactions amount 
// 64 bytes for fileNameHash + fileHash
// remake to separated class
std::vector<unsigned char> Block::binarySerialize() const{
    std::vector<unsigned char> concBlock;
    concBlock.insert(concBlock.end(), previousBlockHash.begin(), previousBlockHash.end());
    
    unsigned char idBytes[sizeof(id)];
    std::memcpy(idBytes, &id, sizeof(id));
    concBlock.insert(concBlock.end(), idBytes, idBytes + sizeof(id));
    
    unsigned char timeBytes[sizeof(timestamp)];
    std::memcpy(timeBytes, &timestamp, sizeof(timestamp));
    concBlock.insert(concBlock.end(), timeBytes, timeBytes + sizeof(timestamp));
    
    int transcationAmount = transactions.size();
    unsigned char amountBytes[sizeof(transcationAmount)];
    std::memcpy(amountBytes, &transcationAmount, sizeof(transcationAmount));
    concBlock.insert(concBlock.end(),amountBytes,amountBytes + sizeof(transcationAmount));

    for (auto &i : transactions){
        std::vector<unsigned char> a = i.binarySerialize();
        concBlock.insert(concBlock.end(), a.begin(), a.end());
    }

    return concBlock;
}
std::string Block::humanReadableFormat() const{
    std::string retString = "Previous block hash: " + hasher->hashToHex(previousBlockHash) + "\n";
    retString += "id " + std::to_string(id) + "\n";
    retString += "timestamp " + std::to_string(timestamp) + "\n";
    retString += "Transactions: \n";
    for(auto& i:transactions){
        retString += hasher->hashToHex(i.binarySerialize()) + "\n";
    }
    retString += "Block hash: " + hasher->hashToHex(blockHash) + "\n";
    return retString;
}