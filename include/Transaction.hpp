#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include<string>
#include<vector>
struct Transaction{
    const std::vector<unsigned char> fileNameHash;
    const std::vector<unsigned char> hash;
    std::vector<unsigned char> binarySerialize() const{
        std::vector<unsigned char> temp(fileNameHash.begin(),fileNameHash.end());
        temp.insert(temp.end(),hash.begin(),hash.end());
        return temp;
    }
    long long size() const{
        return hash.size() + fileNameHash.size();
    }
    Transaction(const std::vector<unsigned char>& fileNameHash,const std::vector<unsigned char>& hash):fileNameHash(fileNameHash),hash(hash){}
    bool operator=(const Transaction& a){
        return (a.fileNameHash == this->fileNameHash) && (a.hash == this->hash);
    }
};

#endif