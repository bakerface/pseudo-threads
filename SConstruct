env = Environment(
    CPPFLAGS="-Os -Wall -Wextra -Werror -Wconversion -ansi -pedantic",
    CPPPATH="include"
)

env.Program("test", [
    "tests/test.c",
    "tests/thread_test.c",
    "tests/semaphore_test.c",
    "tests/timer_test.c"
])
