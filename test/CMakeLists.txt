cmake_minimum_required(VERSION 3.10)

project(MyProject)

# 添加子目录，构建静态库
add_subdirectory(Serial)
add_subdirectory(app)
