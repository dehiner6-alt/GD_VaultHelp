cmake_minimum_required(VERSION 3.25)
project(VaultHelper CXX)

find_package(Geode REQUIRED)

geode_target_include_directories(
    PRIVATE src
)

geode_add_mod(VaultHelper
    src/main.cpp
)
