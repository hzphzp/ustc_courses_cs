# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (rdt_stopwait)
# 指定生成目标
add_executable(rdt_stopwait_receiver, rdt_stopwait_receiver.c)
add_executable(rdt_stopwait_sender, rdt_stopwait_sender.c)