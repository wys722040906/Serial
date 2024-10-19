
#选择生成 动态库 静态库
option(SERIAL_BUILD_SHARED_LIBS "Build CppLinuxSerial shared library" OFF)

if (SERIAL_BUILD_SHARED_LIBS)
  add_library(CppLinuxSerial SHARED)
else()
  add_library(CppLinuxSerial STATIC)
endif()

# 库别名
add_library(CppLinuxSerial::CppLinuxSerial ALIAS CppLinuxSerial)

#制定目标的编译选项
target_compile_features(CppLinuxSerial PRIVATE cxx_std_14)

target_sources(CppLinuxSerial
  PRIVATE 
    SerialPort.cpp)
#为库添加头文件搜索路径  库本身+链接到它的目标 皆可见
#CMake 的生成表达式  根据构建环境确定包含路径  ${CMAKE_CURRENT_SOURCE_DIR}/../include
#CMake 的安装路径  ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} (被安装到/usr/local/include/${PROJECT_NAME})
target_include_directories(
  CppLinuxSerial 
    PUBLIC 
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

#引入CMakePackageConfigHelpers 模块 用于创建和安装 CMake 包配置文件的实用函数
include(CMakePackageConfigHelpers)
#
install(
  TARGETS CppLinuxSerial 
  EXPORT CppLinuxSerialTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)

install(
  EXPORT CppLinuxSerialTargets
  FILE CppLinuxSerialTargets.cmake
  NAMESPACE CppLinuxSerial::
  DESTINATION lib/cmake/CppLinuxSerial
)
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/CppLinuxSerial 
  DESTINATION include
)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CppLinuxSerialConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppLinuxSerial
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    CppLinuxSerialConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/CppLinuxSerialConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CppLinuxSerialConfigVersion.cmake"
  DESTINATION lib/cmake/CppLinuxSerial
)
