find_package(SDL2 REQUIRED)

add_executable(simple-platformer main.c)

target_link_libraries(simple-platformer PRIVATE SDL2::SDL2)

if (MSVC)
    target_compile_options(simple-platformer PRIVATE /W4)
else()
    target_compile_options(simple-platformer PRIVATE -Wall -Wextra -Werror)
endif()

