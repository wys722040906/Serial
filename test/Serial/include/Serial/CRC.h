/**
 * @file CRC.h
 * @author yao
 * @date 2021年1月13日
 * @brief C++实现的CRC校验
 */

#ifndef KDROBOTCPPLIBS_CRC_H
#define KDROBOTCPPLIBS_CRC_H

#include <vector>
#include <stdint.h>

namespace CRC {
    // /**
    //  * @brief CRC8校验和函数
    //  * @param pchMessage 要校验的数据
    //  * @param dwLength 数据流的长度
    //  * @param ucCRC8 初始化的CRC8校验和
    //  * @return 计算得到的CRC8校验和
    //  */
    // uint8_t Get_CRC8_Check_Sum(uint8_t *pchMessage, uint8_t dwLength, uint8_t ucCRC8);

    /**
     * @brief CRC16校验和函数
     * @param pchMessage 要校验的数据
     * @param dwLength 数据流的长度
     * @param wCRC 初始化的CRC16校验和
     * @return 计算得到的CRC16校验和
     */
    uint16_t Get_CRC16_Check_Sum(const uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);

    // /**
    //  * @brief CRC8校验函数
    //  * @param pchMessage 要校验的数据
    //  * @param dwLength 数据流的长度 = 数据 + 校验和
    //  * @return 校验结果
    //  */
    // uint8_t Verify_CRC8_Check_Sum(uint8_t *pchMessage, uint8_t dwLength);

    // /**
    //  * 重载函数
    //  * @param pchMessage 要校验的数据
    //  * @return 校验结果
    //  */
    // inline uint8_t Verify_CRC8_Check_Sum(std::vector<uint8_t> pchMessage) {
    //     return Verify_CRC8_Check_Sum(pchMessage.data(), (uint8_t) pchMessage.size());
    // }

    /**
     * @brief CRC16校验函数
     * @param pchMessage 要校验的数据
     * @param dwLength 数据流的长度 = 数据 + 校验和
     * @return 校验结果
     */
    uint16_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);

    /**
     * 重载函数
     * @param pchMessage 要校验的数据
     * @return 校验结果
     */
    inline uint16_t Verify_CRC16_Check_Sum(std::vector<uint8_t> pchMessage) {
        return Verify_CRC16_Check_Sum(pchMessage.data(), (uint32_t) pchMessage.size());
    }

    /**
     * 重载函数
     * @param pchMessage 要校验的数据
     * @return 校验结果
     */
}

#endif //KDROBOTCPPLIBS_CRC_H
