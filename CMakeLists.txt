# Min version
CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

# Set project
project(rngcpp)

# Compiler warnings
set(CMAKE_CXX_FLAGS "-std=c++20\
                     -Wall\
                     -Werror\
                     -Wpedantic\
                     -Wshadow\
                     -Wunused\
                     -Wconversion\
                     -Wsign-conversion\
                     -Wuseless-cast\
                     -Wformat=2")

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS ON)

# Dependencies
find_package(fmt)

set (SOURCE_FILES main.cpp)
add_executable(rngcpp ${SOURCE_FILES})

# Link dependencies
target_link_libraries(${PROJECT_NAME} fmt::fmt)