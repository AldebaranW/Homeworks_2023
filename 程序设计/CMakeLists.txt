cmake_minimum_required(VERSION 3.10)
project(main)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CS1604_INCLUDE /home/wu/Desktop/judger_student/522030910190/third_party/cs1604/include)
set(CS1604_LIBS /home/wu/Desktop/judger_student/522030910190/third_party/cs1604/lib)

include_directories(${CS1604_INCLUDE})
link_directories(${CS1604_LIBS})

add_executable(main main.cpp field.cpp units.cpp engine.cpp)
target_link_libraries(main libCS1604.a)
