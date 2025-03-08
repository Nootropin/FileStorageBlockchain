#include"File.hpp"
std::vector<unsigned char> File::read() const{
    std::ifstream fileStream(fileName,std::ios::binary);

        if(!fileStream){
            throw std::runtime_error("Error opening file: " + fileName);
        }

        fileStream.seekg(0, std::ios::end);
        std::streampos fileSize = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        std::vector<unsigned char> buffer(fileSize);
        fileStream.read(reinterpret_cast<char*>(buffer.data()), fileSize);

        if(!fileStream){
            throw std::runtime_error("Error reading from file: " + fileName);
        }

        return buffer;
}