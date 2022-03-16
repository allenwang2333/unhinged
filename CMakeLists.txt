cmake_minimum_required(VERSION 3.21)
project(CS_32_PROJECT_4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -O2")

add_executable(main main.cpp AttributeTranslator.cpp MatchMaker.cpp PersonProfile.cpp MemberDatabase.cpp)
add_executable(test test.cpp AttributeTranslator.cpp PersonProfile.cpp MemberDatabase.cpp)
