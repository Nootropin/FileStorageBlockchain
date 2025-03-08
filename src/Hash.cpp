#include"Hash.hpp"
#include<sstream>
#include<iomanip>
std::vector<unsigned char> SHA_256_HASHER::hash(const std::vector<unsigned char>& input) const{
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.data(), input.size());
    SHA256_Final(hash.data(), &sha256);
    return hash;
}
std::string SHA_256_HASHER::hashToHex(const std::vector<unsigned char>& input) const{
    std::stringstream ss;
    for(auto& i:input){
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)i;
    }
    return ss.str();
}