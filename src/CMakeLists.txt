add_executable(simple-platformer main.c)

if (MSVC)
    target_compile_options(simple-platformer PRIVATE /W4)
else()
    target_compile_options(simple-platformer PRIVATE -Wall -Wextra -Werror)
endif()

