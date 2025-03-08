#include "BlockChain.hpp"
bool BlockChain::addBlock(const Block block){
    if(block.id == 0 || block.previousBlockHash == _lastHash){
        if(block.id == _length){
            _blockVector.push_back(block);
            _length++;
            _lastHash = block.blockHash;
            return true;
        }else{
            throw std::runtime_error("Wrong block id: " + std::to_string(block.id));
        }
    }else{
        throw std::runtime_error("Previous block hash is wrong: " + block.hasher->hashToHex(block.previousBlockHash) + "expected: " + block.hasher->hashToHex(_lastHash));
    } return false;
}
std::vector<unsigned char> BlockChain::getLastHash() const{
    return _lastHash;
}
long long BlockChain::getLength() const{
    return _length;
}
Block BlockChain::getBlock(const long long& id) const{
    if(id < _length){
        return _blockVector[id];
    }else{
        throw std::runtime_error("Id of block is over blockchain length");
    }
}
BlockChain::BlockChain(Block block){
    if(block.id == 0){
        _blockVector.push_back(block);
        _length = 1;
        _lastHash = block.blockHash;
    }else{
        throw std::runtime_error("First block id should be 0");
    }
}
BlockChain::BlockChain(){
    _length = 0;
}
std::vector<unsigned char> BlockChain::binarySerialize() const{
    std::vector<unsigned char> output;
    for(auto& i:_blockVector){
        std::vector<unsigned char> ser = i.binarySerialize();
        output.insert(output.end(),ser.begin(),ser.end());
    }
    return output;
}
const std::vector<Block>& BlockChain::getList() const{
    return _blockVector;
}