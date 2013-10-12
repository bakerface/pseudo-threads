e = Environment()

project_name = ARGUMENTS.get("project-name", "e3")
build_type = ARGUMENTS.get("build-type", "")
test_binary = ARGUMENTS.get("test-binary", "test")

e.Append(CPPPATH=["include"])
e.Append(CCFLAGS=["-Wall", "-Wextra", "-Wconversion", "-Werror"])
e.Append(CCFLAGS=["-ansi", "-pedantic", "-ffreestanding", "-nostdlib"])
e.Clean(test_binary, Glob(".sconsign.dblite"))

if build_type == "":
    e.Append(CCFLAGS=["-g", "-O0", "-fprofile-arcs", "-ftest-coverage"])
    e.Append(LIBS=["gcov"])
    e.Clean(test_binary, Glob("src/*.gcno"))
    e.Clean(test_binary, Glob("src/*.gcda"))
    e.Clean(test_binary, Glob("tests/*.gcno"))
    e.Clean(test_binary, Glob("tests/*.gcda"))
    
    coverage = e.Command("coverage", [], [
        "./" + test_binary,
        "lcov -b . -c -d src -o " + project_name + ".coverage",
        "genhtml -o $TARGET " + project_name + ".coverage"])
        
    complexity = e.Command("complexity", Glob("src/*.c"), [
        "pmccabe -t -v $SOURCES"])
    
    e.Depends(coverage, "test")
    e.Depends(complexity, coverage)
    e.Clean(test_binary, project_name + ".coverage")
    e.Clean(test_binary, "coverage")
    e.Program(test_binary, [Glob("src/*.c"), Glob("tests/*.c")])

elif build_type == "release":
    e.Append(CCFLAGS=["-Os"])
    library = e.StaticLibrary(project_name, [Glob("src/*.c")])
    symbols = e.Command("symbols", library, ["nm -S $SOURCE"])

