cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (mh)

# search for Boost
find_package(Boost)
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )

#profiling
SET(CMAKE_CXX_FLAGS_PROFILE "-pg -O0")

#source
add_executable(mh mh_tests.cpp)

