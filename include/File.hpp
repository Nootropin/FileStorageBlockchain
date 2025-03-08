#ifndef FILE_HPP
#define FILE_HPP
#include<string>
#include<fstream>
#include<vector>
class File{
    public:
        File(const std::string& fileName):fileName(fileName){};
        std::vector<unsigned char> read() const;
    private:
        const std::string fileName;
};
#endif // FILE_HPP