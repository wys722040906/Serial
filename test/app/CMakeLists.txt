cmake_minimum_required(VERSION 3.22)
project(test)
set(CMAKE_CXX_STANDARD 14)

# 指定库的链接目录
link_directories("/usr/local/lib")
# 添加 /usr/local/include 到头文件搜索路径 -- 全局命令，影响所有 CMakeLists.txt 文件
# include_directories(/usr/local/include)
# 添加 CppLinuxSerial 头文件的包含目录
# include_directories("/usr/local/include/CppLinuxSerial")
find_package(CppLinuxSerial REQUIRED) #仅找一个 /usr/local下的camke配置包


#添加源文件
add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# 包含目录
target_include_directories(test PRIVATE 
    usr/local/include
)
#链接库文件
target_link_libraries(test PRIVATE
     CppLinuxSerial
     Serial
)    

