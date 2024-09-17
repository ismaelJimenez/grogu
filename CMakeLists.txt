cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(grogu)

# ---- Create binary ----

add_executable(grogu src/main.cpp)
target_compile_features(grogu PRIVATE cxx_std_17)

# ---- Dependencies ----

include(cmake/CPM.cmake)
