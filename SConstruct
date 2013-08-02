env = Environment(
    CPPFLAGS="-Os -Wall -Wextra -Werror -Wconversion -ansi -pedantic",
    CPPPATH="include"
)

env.Program("test", [
    "src/xml.c",

    "tests/test.c",
    "tests/thread_test.c",
    "tests/semaphore_test.c",
    "tests/timer_test.c",
    "tests/xml_test.c"
])
