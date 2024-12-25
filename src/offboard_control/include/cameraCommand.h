#include <cstring> // for memset

struct ooCommandStruct
{
    unsigned char uc55;                // 
    unsigned char ucAA;                // 
    unsigned char ucCmd;               // 指令码
    unsigned char ucError;             // 错误码，子指令
    unsigned int lenData;              // 附加数据字节数
    union {                            // 附加数据
        char pcData[8];                // 1字节
        unsigned char pucData[8];      // 1字节
        unsigned short pusData[4];     //2字节
        int piData[2];                 //4字节
        unsigned int puiData[2];       //4字节
        float pfData[2];               //4字节
        double pdData[1];              //8字节
    };
};

void startMeasure(ooCommandStruct &cmd)
{
    cmd.uc55 = 0x55;
    cmd.ucAA = 0xAA;
    cmd.ucCmd = 5;
    cmd.ucError = 41;
    cmd.lenData = 0;
    std::memset(cmd.pcData, 0, sizeof(cmd.pcData));
}

void endMeasure(ooCommandStruct &cmd)
{
    cmd.uc55 = 0x55;
    cmd.ucAA = 0xAA;
    cmd.ucCmd = 5;
    cmd.ucError = 250;
    cmd.lenData = 0;
    std::memset(cmd.pcData, 0, sizeof(cmd.pcData));
}
void serializeCommand(const ooCommandStruct &cmd, unsigned char *buffer)
{
    std::memcpy(buffer, &cmd, sizeof(cmd));
}
// 反序列化
void deserializeCommand(const unsigned char *buffer, ooCommandStruct &cmd)
{
    std::memcpy(&cmd, buffer, sizeof(cmd));
}