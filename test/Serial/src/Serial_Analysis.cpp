#include "../include/Serial/Serial_Analysis.h"

// 数据帧打包函数
std::vector<uint8_t> mn::CppLinuxSerial::CreateFrame(uint16_t functionCode, const std::vector<uint8_t>& data) {
    std::vector<uint8_t> frame;

    // 添加帧头
    frame.push_back(FRAME_START);

    // 添加功能码（2字节）
    frame.push_back((functionCode >> 8) & 0xFF);  // 功能码高字节
    frame.push_back(functionCode & 0xFF);         // 功能码低字节

    // 添加数据长度
    frame.push_back(static_cast<uint8_t>(data.size()));

    // 添加数据区
    frame.insert(frame.end(), data.begin(), data.end());

    // 计算CRC16校验和（从功能码到数据区的部分进行校验）
    uint16_t crc16 = CRC::Get_CRC16_Check_Sum(&frame[1], frame.size() - 1, 0xFFFF);

    // 添加CRC16校验码
    frame.push_back(crc16 & 0xFF);         // CRC16低字节
    frame.push_back((crc16 >> 8) & 0xFF);  // CRC16高字节

    // 添加帧尾
    frame.push_back(FRAME_END);

    return frame;
}


// 数据帧解包函数
bool mn::CppLinuxSerial::ParseFrame(const std::vector<uint8_t>& frame) {
    // 检查帧长度
    if (frame.size() < 5) { // 需要最少5个字节来包含帧头、功能码、数据长度和帧尾
        if(LogPrint)
        std::cerr << "帧长度不足！" << std::endl;
        return false;
    }

    // 检查帧头和帧尾
    if (frame.front() != FRAME_START || frame.back() != FRAME_END) {
        if(LogPrint)
        std::cerr << "帧头或帧尾错误！" << std::endl;
        return false;
    }

    // 提取功能码
    uint16_t functionCode = (frame[1] << 8) | frame[2];
    if(LogPrint)
    std::cout << "功能码: 0x" << std::hex << functionCode << std::dec << std::endl;

    // 提取数据长度
    uint8_t dataLength = frame[3];
    if(LogPrint)
    std::cout << "数据长度: " << (int)dataLength << std::endl;

    // 检查数据长度是否有效
    if (frame.size() < 5 + dataLength + 2) { // 5是帧头和功能码、数据长度，2是CRC16
        if(LogPrint)
        std::cerr << "数据长度无效！" << std::endl;
        return false;
    }

    // 提取数据区
    std::vector<uint8_t> data(frame.begin() + 4, frame.begin() + 4 + dataLength);
    if(LogPrint)
    std::cout << "数据内容: ";
    for (uint8_t byte : data) {
        if(LogPrint)
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::dec << std::endl; // 恢复十进制输出格式

    // 提取接收到的CRC16校验码
    uint16_t receivedCRC = (frame[4 + dataLength + 1] << 8) | frame[4 + dataLength];
    if(LogPrint)
    std::cout << "接收到的CRC16校验码: 0x" << std::hex << receivedCRC << std::dec << std::endl;

    // 计算CRC16校验和（从功能码到数据区）
    uint16_t calculatedCRC = CRC::Get_CRC16_Check_Sum(&frame[1], 3 + dataLength, 0xFFFF);
    if(LogPrint)
    std::cout << "计算得到的CRC16校验码: 0x" << std::hex << calculatedCRC << std::dec << std::endl;

    // 校验CRC16
    if (receivedCRC == calculatedCRC) {
        if(LogPrint)
        std::cout << "数据帧校验成功！" << std::endl;
        return true;
    } else {
        if(LogPrint)
        std::cerr << "数据帧校验失败！" << std::endl;
        return false;
    }
}


