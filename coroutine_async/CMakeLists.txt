cmake_minimum_required(VERSION 3.15)

project(coroutine_async)

include_directories(./include)

aux_source_directory(./src SRC)

file(GLOB_RECURSE HEADERS ./include/*.h ./include/*.hpp)

add_library(${PROJECT_NAME} ${SRC} ${HEADERS})
