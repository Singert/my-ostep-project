set(CMAKE_COMPILE_COMMANDS ON)
project(reserve)

add_executable(reserve reserve/reserve.c)

add_compile_options(-Wall -Wextra -Werror -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")