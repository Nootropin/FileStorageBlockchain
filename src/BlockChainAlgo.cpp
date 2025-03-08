#include "BlockChainAlgo.hpp"
std::vector<unsigned char> BlockChainAlgo::getFileLastHash(const std::vector<unsigned char> fileNameHash) const
{
    for (int i = blockchain->getLength() - 1; i >= 0; i--)
    {
        Block blck = blockchain->getBlock(i);
        for (auto &j : blck.transactions)
        {
            if (j.fileNameHash == fileNameHash)
            {
                return j.hash;
            }
        }
    }
    return {0};
}

std::vector<std::vector<unsigned char>> BlockChainAlgo::getFileHashes(const std::vector<unsigned char> fileNameHash) const
{
    std::vector<std::vector<unsigned char>> vReturn;
    for (int i = blockchain->getLength() - 1; i >= 0; i--)
    {
        Block blck = blockchain->getBlock(i);
        for (auto &j : blck.transactions)
        {
            if (j.fileNameHash == fileNameHash)
            {
                vReturn.push_back(j.hash);
            }
        }
    }
    if (vReturn.size() == 0)
        return {{0}};
    return vReturn;
}

int BlockChainAlgo::addFileToBlock(std::string fileName) 
{
    try{
        File f(fileName);
        const auto fileText = f.read();
        const std::vector<unsigned char> vfileName(fileName.begin(), fileName.end());
        const std::vector<unsigned char> fileNameHash = hash->hash(vfileName);
        const std::vector<unsigned char> fileTextHash = hash->hash(fileText);
        Transaction t = Transaction(fileNameHash, fileTextHash);
        vBuffer.push_back(t);
        return 0;
    } catch(std::exception e){
        return -1;
    }
}

int BlockChainAlgo::createNewBlock()
{
    if (vBuffer.size() == 0)
    {
        return -1;
    }
    else
    {
        time_t currentTime;
        if (this->blockchain->getLength() == 0)
        {
            std::vector<unsigned char> zeroVector(32, 0);
            currentTime = time(nullptr);
            Block header(zeroVector, 0, currentTime, vBuffer, hash);
            blockchain->addBlock(header);
        }
        else
        {
            currentTime = time(nullptr);
            auto topHash = blockchain->getLastHash();
            long long topId = blockchain->getLength();
            Block newBlock(topHash, topId, currentTime, vBuffer, hash);
            blockchain->addBlock(newBlock);
        }
        vBuffer.erase(vBuffer.begin(),vBuffer.end());
        return 0;
    }
}
std::string BlockChainAlgo::getBlockSerialized(int id) const
{
    if (id < blockchain->getLength())
    {
        Block output = blockchain->getList()[id];
        return output.humanReadableFormat();
    }
    else
    {
        return "";
    }
}
int BlockChainAlgo::saveBlockchain(std::string outputFileName) const
{
    std::fstream f(outputFileName, std::ios::binary | std::ios::out);
    std::vector<unsigned char> out = blockchain->binarySerialize();
    f.write(reinterpret_cast<const char *>(out.data()), out.size());
    f.close();
    return 0;
}