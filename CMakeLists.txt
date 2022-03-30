cmake_minimum_required(VERSION 3.21)
project(snacner)

set(CMAKE_CXX_STANDARD 98)

add_executable(snacner main.cpp module/argparse.cpp module/argparse.h)
