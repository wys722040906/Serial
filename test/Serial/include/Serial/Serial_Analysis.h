#ifndef __SERIAL_ANALYSIS_H
#define __SERIAL_ANALYSIS_H

#include <iostream>
#include <vector>
#include <stdint.h>
#include "CRC.h"
#include <mutex>
#include <condition_variable>


/*
数据帧格式：
帧头 (Frame Start)： 固定为 0xAA
功能码 (Function Code)： 2 字节，表示功能（可以是命令、操作类型等）
数据长度 (Data Length)： 1 字节，表示数据区的长度
数据区 (Data)： 可变长度的数据
CRC16 校验码： 2 字节，用于校验数据的完整性
帧尾 (Frame End)： 固定为 0x55

数据帧的长度为 7 + 数据长度 + 2，其中 7 为帧头、帧尾、功能码、数据长度、CRC16 校验码的长度。
*/


// 常量定义
const uint8_t FRAME_START = 0xAA;
const uint8_t FRAME_END = 0x55;

const bool LogPrint = false;

namespace mn{ 
    namespace CppLinuxSerial{

// 数据帧打包函数
std::vector<uint8_t> CreateFrame(uint16_t functionCode, const std::vector<uint8_t>& data);

// 数据帧解包函数
bool ParseFrame(const std::vector<uint8_t>& frame);

//环形缓冲区

template<typename T>
class CircularBuffer {
public:
    CircularBuffer(size_t size) 
        : buffer(size), head(0), tail(0), full(false) {}

    void put(const T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        // 等待直到有空位
        not_full.wait(lock, [this]() { return !full; });

        buffer[head] = item;
        head = (head + 1) % buffer.size();

        if (head == tail) { // 如果环形缓冲区满了，更新尾指针
            tail = (tail + 1) % buffer.size();
        }

        full = (head == tail);
        not_empty.notify_one(); // 通知有可读取数据
    }

    T get() {
        std::unique_lock<std::mutex> lock(mutex);
        // 等待直到有数据
        not_empty.wait(lock, [this]() { return !empty(); });

        T item = buffer[tail];
        tail = (tail + 1) % buffer.size();
        full = false;

        not_full.notify_one(); // 通知有空位
        return item;
    }

    bool empty() const {
        return (!full && (head == tail));
    }

    bool is_full() const {
        return full;
    }

private:
    std::vector<T> buffer;
    size_t head; // 写入位置
    size_t tail; // 读取位置
    bool full; // 表示缓冲区是否满
    mutable std::mutex mutex;
    std::condition_variable not_full; // 条件变量，缓冲区不满时的通知
    std::condition_variable not_empty; // 条件变量，缓冲区不空时的通知
};

    }

}



#endif

