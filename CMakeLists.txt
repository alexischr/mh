cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (mh)

# search for Boost version 1.34
find_package(Boost)

link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )


add_executable(mh mh.cpp)

