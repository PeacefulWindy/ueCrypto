cmake_minimum_required(VERSION 3.25)

project(dllCrypto)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(src/rsa srcs)

find_package(cryptopp CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED ${srcs})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)