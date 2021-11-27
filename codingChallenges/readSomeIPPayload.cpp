#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include <winsock.h>


struct Header
{
    uint32_t msg_id{0};
    uint32_t len{0};
    uint32_t req_id{0};
    uint8_t protocol_version{0};
    uint8_t iface_version{0};
    uint8_t msg_type{0};
    uint8_t ret_code{0};
};

class Reader
{
public:
    explicit Reader(const std::string& binFileName) : binFileName_(binFileName), file_(binFileName_, std::ios::in | std::ios::out | std::ios::binary)
    {};

    void read()
    {
        readSomeIPHeader();
        readPayLoadLength();
        readPayLoad();
    }

    void showSomeIPHeader() const
    {
        printf("msg_id : %x, len : %x, req_id: %x \n", header_.msg_id, header_.len, header_.req_id);
        printf("protocol_version : %x, iface_version : %x, msg_type: %x, ret_code: %x \n", header_.protocol_version, header_.iface_version, header_.msg_type, header_.ret_code);
    
        printf("payload length: %x \n", payloadLength_);
    }
private:
    void reverseInt32(uint32_t& num)
    {
        num = htonl(num);
        uint32_t msg_id;
        msg_id = htonl(msg_id);
    }

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

    void readPayLoadLength()
    {
        readUint32WithSwap(file_, payloadLength_);
    }

    void readSomeIPHeader()
    {
        readUint32WithSwap(file_, header_.msg_id);
        readUint32WithSwap(file_, header_.len);
        readUint32WithSwap(file_, header_.req_id);

        readByte(file_, header_.protocol_version);
        readByte(file_, header_.iface_version);
        readByte(file_, header_.msg_type);
        readByte(file_, header_.ret_code);
    }

    void readPayLoad()
    {  
        std::map<uint8_t, uint8_t> WireTypeBytes;
        WireTypeBytes[0] = 1;
        WireTypeBytes[1] = 2;
        WireTypeBytes[2] = 4;
        WireTypeBytes[3] = 8;

        
        uint8_t firstByte;
        uint8_t secondByte;

        uint16_t dataId;
        readByte(file_, firstByte);
        readByte(file_, secondByte);

        uint8_t wiretypeMask = 0xf0;
        uint8_t wireType = (firstByte&wiretypeMask)>>4;
        uint8_t dataIdMask = 0x0f;

        uint8_t dataIdHigherPart = firstByte&dataIdMask;
        dataId = ((static_cast<uint16_t>(dataIdHigherPart)) << 8) | static_cast<uint16_t>(secondByte);

        printf("wiretype = %x\n", wireType);
        printf("dataId : %x\n", dataId);
    }
private:
    std::string binFileName_{};
    Header header_{};
    uint32_t payloadLength_{0};

    std::fstream file_;
      
};

int main(int argc, char* argv[])
{
    std::string binFile = "input_data.bin";
    Reader r(binFile);
    r.read();
    r.showSomeIPHeader();


    return 0;
}