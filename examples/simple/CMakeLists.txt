cmake_minimum_required(VERSION 3.12)
project(whisper-simple)

set(TARGET simple)
add_executable(${TARGET} simple.cpp)

target_link_libraries(${TARGET} PRIVATE common whisper ${CMAKE_THREAD_LIBS_INIT})

# Include thread support
find_package(Threads REQUIRED)