#include<iostream>
#include "Hash.hpp"
#include "BlockChain.hpp"
#include "File.hpp"
#include "Block.hpp"
#include "Deserializer.hpp"
#include "BlockChainAlgo.hpp"
#include "Gui.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
int main(int argc, char *argv[]){
    SHA_256_HASHER hash;
    Deserializer des;
    time_t currentTime = 0;
    if(argc > 1 && argv[1][0] == 'g'){
        QApplication m(argc, argv);
        BlockchainWindow n = BlockchainWindow();
        n.show();
        return m.exec();
    }else{
    std::cout << "Enter 1 to create new BlockChain\nEnter 2 to import BlockChain from file" << std::endl;
    int c;
    std::cin >> c;
    BlockChain fileChain = BlockChain();
    if(c == 1){
        fileChain = BlockChain();
    }if(c == 2){
        std::string inputName;
        std::cout << "Enter file path" << std::endl;
        std::cin >> inputName;
        File f(inputName);
        fileChain = des.deserialize(f.read(),&hash);
    }
    BlockChainAlgo blockAlgo = BlockChainAlgo(&hash,&fileChain);
    while(true){
        std::cout << "Enter 1 to add new file to block\nEnter 2 to create new block\nEnter 3 to get block serialized\nEtner 4 to save blockchain\nEnter 5 to check file hash\nEnter 6 to view file hashes\nEnter 7 to exit" << std::endl;
        int t;
        std::cin >> t;
        if(t == 1){
            std::string s;
            std::cout << "Enter file path: " << std::endl;
            std::cin >> s;
            std::cout << blockAlgo.addFileToBlock(s);
        }else if(t == 2){
            blockAlgo.createNewBlock();
        }else if(t == 3){
            long long id;
            std::cout << "Enter block id: ";
            std::cin >> id;
            std::cout << blockAlgo.getBlockSerialized(id);
        }else if(t == 4){
            std::string outputFileName;
            std::cout << "Enter output file name" << std::endl;
            std::cin >> outputFileName;
            blockAlgo.saveBlockchain(outputFileName);
        }else if(t == 5){
            std::string fileName;
            std::cout << "Enter file name" << std::endl;
            std::cin >> fileName;
            std::vector<unsigned char> vfileName(fileName.begin(),fileName.end());
            std::vector<unsigned char> fileNameHash = hash.hash(vfileName);
            try{
                std::vector<unsigned char> fileHash = blockAlgo.getFileLastHash(fileNameHash);
                std::cout << std::endl << "File hash in block = " << hash.hashToHex(fileHash) << std::endl;
                File f(fileName);
                std::vector<unsigned char> vFileContent = f.read();
                std::vector<unsigned char> vFileHash = hash.hash(vFileContent);
                std::string hex = hash.hashToHex(vFileHash);
                std::cout << "Local file hash = " << hex << std::endl;
            }catch (std::exception e){
                std::cerr << e.what() << std::endl;
            }
        }
        else if(t == 6){
            std::string fileName;
            std::cout << "Enter file name" << std::endl;
            std::cin >> fileName;
            std::vector<unsigned char> vfileName(fileName.begin(),fileName.end());
            std::vector<unsigned char> fileNameHash = hash.hash(vfileName);
            try{
                std::vector<std::vector<unsigned char>> fileHashes = blockAlgo.getFileHashes(fileNameHash);
                int counter = 0;
                for(auto&i:fileHashes){
                    std::cout << "File hash id " << counter << " in block = " << hash.hashToHex(i) << std::endl;
                    counter+=1;
                }
                File f(fileName);
                std::vector<unsigned char> vFileContent = f.read();
                std::vector<unsigned char> vFileHash = hash.hash(vFileContent);
                std::string hex = hash.hashToHex(vFileHash);
                std::cout << "Local file hash = " << hex << std::endl;
            }catch (std::exception e){
                std::cerr << e.what() << std::endl;
            }
        }else if(t == 7){
            break;
        }
    }
    }
}