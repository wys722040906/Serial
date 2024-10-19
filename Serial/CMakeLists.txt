# 声明项目名称
project(Serial)
cmake_minimum_required(VERSION 3.10)

add_library(Serial STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CRC.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Serial_Analysis.cpp
)

target_include_directories(Serial PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 定义库的安装位置，供外部项目使用 
# 默认安装到 ${CMAKE_INSTALL_PREFIX}/
# 指定安装目录 set(${CMAKE_INSTALL_PREFIX} /usr/local)
install(TARGETS Serial DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
