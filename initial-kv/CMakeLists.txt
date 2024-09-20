set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(kv)

add_executable(kv kv/kv.c)

add_compile_options(-Wall -Wextra -Werror -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")