cmake_minimum_required(VERSION 3.16)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME proj_name)
project(hw-02_huffman CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR "include/")
set(CFlag -O2 -Wextra -Wall -Werror -std=c++17)

file(GLOB SRCS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_sources(${PROJECT_NAME} PRIVATE ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFlag})

add_executable(tests 
    test/test.cpp      
)

target_include_directories(tests PRIVATE 
    ${INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(tests PRIVATE "src/huffmanSrc.cpp" "src/parser.cpp")

target_include_directories(tests PRIVATE ${INCLUDE_DIR})
target_compile_options(tests PRIVATE ${CFlag})


enable_testing()
add_test(NAME tests COMMAND tests)