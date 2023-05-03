cmake_minimum_required(VERSION 3.8)

# 这里的 tabulateDemo 可以换为你喜欢的名字
project(StudentManagementWithGoodTable)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(main main.cpp)