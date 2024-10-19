#include <iostream>
#include <string>
#include <vector>

#include <CppLinuxSerial/SerialPort.hpp>
#include <Serial/CRC.h>
#include <Serial/Serial_Analysis.h>
#include <chrono>
#include <thread>
#include <atomic>

using namespace mn::CppLinuxSerial;

std::atomic<uint32_t> shared_count(0); 

class Timer {
public:
    Timer() : running_(false) {}

    // 启动计时器
    void start() {
        running_ = true;
        counting_thread_ = std::thread(&Timer::count, this);
    }

    // 停止计时器
    void stop() {
        running_ = false;
        if (counting_thread_.joinable()) {
            counting_thread_.join(); // 等待线程结束
        }
    }

    // 获取经过的时间（秒）
    double getElapsedTime() const {
        return elapsed_time_;
    }

private:
    std::atomic<bool> running_; // 使用原子变量确保线程安全
    std::thread counting_thread_;
    double elapsed_time_ = 0.0; // 经过的时间（秒）

    // 计时线程的执行函数
    void count() {
        auto start_time = std::chrono::high_resolution_clock::now();
        while (running_) {
            auto current_time = std::chrono::high_resolution_clock::now();
            elapsed_time_ = std::chrono::duration<double>(current_time - start_time).count();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 每 1000 毫秒更新一次
			std::cout << "serial port read rate" << shared_count << std::endl;
			shared_count = 0;
        }
    }
};


CircularBuffer<std::vector<uint8_t>> buffer(64);


int main() {

	SerialPort serialPort("/dev/ttyACM0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	serialPort.SetTimeout(100); // Block for up to 100ms to receive data
	serialPort.Open();

	// serialPort.Write("Hello");
	
//----------------------------------------------发送数据帧---
	// uint16_t functioncode = 0x0001;
	// std::vector<uint8_t> tx_data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
	// std::vector<uint8_t> tx_data_frame = CreateFrame(functioncode, tx_data);
	// serialPort.WriteBinary(tx_data_frame);

//---------------------------------------------接收数据帧---
	std::vector<uint8_t> rx_data_frame;
	// std::vector<uint8_t> read_data_frame = serialPort.ReadBinary(readData);
	// std::vector<uint8_t> read_data = ParseFrame(read_data_frame);
	// std::cout << "Read data = " << std::string(read_data.begin(), read_data.end()) << std::endl;

	// Timer timer;
	// timer.start(); 
	while(true){
//----------------------------------------------接受数据---
		serialPort.ReadBinary(rx_data_frame);

		static uint8_t count = 1;
		if(count && !rx_data_frame.empty()){
		buffer.put(rx_data_frame);
		count++;
		}
		if(count == 11){	
			count = 0;
			for(auto i = 0; i < 10; i++){
				std::vector<uint8_t> tx_data_frame = buffer.get();
				std::cout << "Read data = ";
				for(auto byte : rx_data_frame){
					std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
				}
				std::cout << std::dec << std::endl;
			}
			return 0;
		}
		
		// if(rx_data_frame.size() > 0 ){
		// 	if(ParseFrame(rx_data_frame) && !rx_data_frame.empty() ){
		// 		std::cout << "Read data = ";
		// 		for(auto byte : rx_data_frame){
		// 			std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
		// 		}
		// 		std::cout << std::dec << std::endl;
		// 	}
		// 	rx_data_frame.clear();	
		// 	shared_count++;
		// }
		rx_data_frame.clear();

//-----------发送数据----------
		// serialPort.WriteBinary(tx_data_frame);
		// std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 每 1000 毫秒发送一次

	}
	// timer.stop();
	// std::cout << "Elapsed time = " << timer.getElapsedTime() << " seconds" << std::endl;


	serialPort.Close();
	return 0;
}
