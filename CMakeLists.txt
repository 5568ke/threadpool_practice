cmake_minimum_required(VERSION 3.0)

project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(ThreadPool ThreadPool.cpp)
add_subdirectory(thirdparty/concurrentqueue)


target_link_libraries(ThreadPool PRIVATE concurrentqueue pthread)





