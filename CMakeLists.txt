cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(expresser)

add_executable(${PROJECT_NAME} src/main.cpp src/tokenizer.cpp src/tree.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE gvc cgraph cdt)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
