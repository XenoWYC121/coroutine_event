cmake_minimum_required(VERSION 3.15)

project(test_server)

include_directories(./include ../coroutine_async/include)

aux_source_directory(./src SRC)

file(GLOB_RECURSE HEADERS ./include/*.h ./include/*.hpp)

link_libraries(coroutine_async)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})