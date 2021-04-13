cmake_minimum_required(VERSION 3.19)
project(M4101C_Projet)

set(CMAKE_CXX_STANDARD 11)

add_executable(M4101C_Projet main.cpp interrogation_room.cpp interrogation_room.h detective.cpp detective.h cop.cpp cop.h disruptor.cpp disruptor.h lightswitch.cpp lightswitch.h suspect.h utils.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(M4101C_Projet PRIVATE Threads::Threads)