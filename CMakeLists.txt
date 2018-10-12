cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
   fileutil.hpp
)

project(msfa)

add_executable(${PROJECT_NAME} "main.cpp")

# https://stackoverflow.com/questions/17470350/c-cmake-how-to-add-a-linker-flag-to-an-unused-library-when-the-library-is-sp
# https://stackoverflow.com/questions/33149878/experimentalfilesystem-linker-error
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lstdc++fs)
