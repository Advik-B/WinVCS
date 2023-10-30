cmake_minimum_required(VERSION 3.26)
project(WinVCS)

set(CMAKE_CXX_STANDARD 17)


add_executable(WinVCS main.cpp)
target_link_libraries(WinVCS bit7z/lib/x64/Release/bit7z.lib)
target_include_directories(WinVCS PUBLIC bit7z/include)