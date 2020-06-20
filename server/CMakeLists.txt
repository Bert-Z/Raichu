# cmake 最低版本需求
cmake_minimum_required(VERSION 2.8)

# 工程名称
project(server)

# 设置
set(CMAKE_CXX_STANDARD 17)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加子目录
add_subdirectory(datanode)

# 编译源码生成目标
add_executable(server server.cpp)

# 添加链接库
target_link_libraries(server DataNodeLib)

