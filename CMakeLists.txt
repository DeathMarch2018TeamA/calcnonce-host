cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD, 14)

include_directories(include/)
include_directories(lib/)

FILE(GLOB SOURCE src/*)

add_executable(
    calcnonce-host
    ${SOURCE}
    lib/crypto-algorithms/sha256.c
)
