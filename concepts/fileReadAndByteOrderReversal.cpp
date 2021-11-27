#include <iostream>
#include <fstream>
#include <string>
#include <winsock.h>

class Reader
{
public:
    explicit Reader(const std::string& binFileName) : binFileName_(binFileName), 
                                                      file_(binFileName_, std::ios::in | std::ios::out | std::ios::binary)
    {};

    void readUint32WithSwap(std::fstream& file, uint32_t& member)
    {
        uint32_t fourBytes;
        file.read(reinterpret_cast<char *>(&fourBytes), sizeof(fourBytes));
        member = htonl(fourBytes);
    }

    void readByte(std::fstream& file, uint8_t& member)
    {
        file.read(reinterpret_cast<char *>(&member), sizeof(member));
    }
private:
    std::string binFileName_{};
    std::fstream file_;      
};