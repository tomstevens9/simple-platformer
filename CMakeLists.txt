cmake_minimum_required(VERSION 3.14)

# Name the project and specify version + languages
project(SimplePlatformer
        VERSION 1.0
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(simple-platformer src/main.c)

# Optionally set extra warnings (opinionated)
if (MSVC)
    target_compile_options(simple-platformer PRIVATE /W4)
else()
    target_compile_options(simple-platformer PRIVATE -Wall -Wextra -Werror)
endif()

