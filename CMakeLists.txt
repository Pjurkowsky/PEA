cmake_minimum_required(VERSION 3.0.0)
project(project1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(program main.cpp utils/Menu.cpp utils/Timer.cpp utils/RandomGenerator.cpp utils/Tester.cpp Graph.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)
include(CPack)