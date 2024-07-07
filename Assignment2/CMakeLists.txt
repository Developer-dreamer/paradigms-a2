cmake_minimum_required(VERSION 3.11) # Specify the minimum version for CMake

project(paradigms-a2) # Define the project name

set(CMAKE_CXX_STANDARD 17) # Set C++ standard
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# Add the executable
add_executable(paradigms-a2
        Assignment2.cpp
        ConsoleProcessor.h
        ConsoleProcessor.cpp
        FileProcessor.h
        FileProcessor.cpp
        ProgramBackup.h
        ProgramBackup.cpp
        TextProcessor.h
        TextProcessor.cpp
        )

# If you have additional libraries to include, use target_link_libraries
# target_link_libraries(paradigms-a2 someLibrary)