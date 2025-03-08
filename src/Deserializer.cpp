#include "Deserializer.hpp"
BlockChain Deserializer::deserialize(std::vector<unsigned char> vInput, const SHA_256_HASHER* hash) const{
        std::vector<unsigned char> nullHash(32,0);
        long long nullId;
        time_t nullTime;
        int nullTransactionsAmount;
        // reading null block
        nullHash.assign(vInput.begin(),vInput.begin() + 32);
        std::memcpy(&nullId, vInput.data() + 32, 8);
        std::memcpy(&nullTime, vInput.data() + 40, 8);
        std::memcpy(&nullTransactionsAmount, vInput.data() + 48, 4);
        // reading null block transactions
        std::vector<Transaction> nullTrans;
        vInput.assign(vInput.begin() + 52,vInput.end());
        for(int i = 0;i<nullTransactionsAmount;i++){
            std::vector<unsigned char> fileNameHash(32,0);
            std::vector<unsigned char> fileHash(32,0);
            fileNameHash.assign(vInput.begin(),vInput.begin() + 32);
            fileHash.assign(vInput.begin() + 32,vInput.begin() + 64);
            Transaction temp(fileNameHash,fileHash);
            nullTrans.push_back(temp);
            vInput.assign(vInput.begin() + 64,vInput.end());
        }
        // initing null block
        Block header(nullHash,0,nullTime,nullTrans,hash);
        // initing blockchain
        BlockChain chain(header);
        while(vInput.size() != 0){ // reading left blocks
            std::vector<unsigned char> iterHash(32,0);
            long long iterId;
            time_t iterTime;
            int iterTransactionsAmount;
            iterHash.assign(vInput.begin(),vInput.begin() + 32);
            std::memcpy(&iterId, vInput.data() + 32, 8);
            std::memcpy(&iterTime, vInput.data() + 40, 8);
            std::memcpy(&iterTransactionsAmount, vInput.data() + 48, 4);
            std::vector<Transaction> ntrans;
            vInput.assign(vInput.begin() + 52,vInput.end());
            for(int i = 0;i<iterTransactionsAmount;i++){
                std::vector<unsigned char> nfileNameHash(32,0);
                std::vector<unsigned char> nfileHash(32,0);
                nfileNameHash.assign(vInput.begin(),vInput.begin() + 32);
                nfileHash.assign(vInput.begin() + 32,vInput.begin() + 64);
                Transaction ntemp(nfileNameHash,nfileHash);
                ntrans.push_back(ntemp);
                vInput.assign(vInput.begin() + 64,vInput.end());
            }
            
            Block neBlock(iterHash,iterId,iterTime,ntrans,hash);
            chain.addBlock(neBlock);
        }
        return chain;
}