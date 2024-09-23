set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(UTILITIES)

add_executable(wcat src/wcat.c)
add_compile_options(-Wall -Werror -Wextra -pthread)