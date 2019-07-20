#include "catch.hpp"

#include <Runner.hpp>
#include <string>

namespace {

std::string getTestsDirPath()
{
    return PATH_TO_UNIT_TESTS_DIR;
}

std::string matrixFileFullPath(const std::string& i_file_name)
{
    return getTestsDirPath() + "/Maps/" + i_file_name;
}

}

TEST_CASE("<Runner><InvalidFile>")
{
    const auto argc = 3;
    const char* argv[] = {
        "./Runner",
        "-f", "InvalidFile.txt"
    };
    REQUIRE_THROWS(Runner(argc, argv));
}

TEST_CASE("<Runner><NoValueForFile>")
{
    const auto argc = 2;
    const char* argv[] = {
        "./Runner",
        "-f"
    };
    REQUIRE_THROWS(Runner(argc, argv));
}

TEST_CASE("<Runner>")
{
    const auto file = matrixFileFullPath("Solvable3x3.txt");
    const auto argc = 3;
    const char* argv[] = {
        "./Runner",
        "-f", file.c_str()
    };
    REQUIRE_NOTHROW(Runner(argc, argv));
    auto runner = Runner(argc, argv);
    REQUIRE_NOTHROW(runner.run());
    REQUIRE(!runner.hasSomethingToRun());
}

TEST_CASE("<Runner><-v><short>")
{
    const auto file = matrixFileFullPath("Solvable3x3.txt");
    const auto argc = 5;
    const char* argv[] = {
        "./Runner",
        "-v", "short",
        "-f", file.c_str()
    };
    REQUIRE_NOTHROW(Runner(argc, argv));
    auto runner = Runner(argc, argv);
    REQUIRE_NOTHROW(runner.run());
    REQUIRE(!runner.hasSomethingToRun());
}

TEST_CASE("<Runner><-v><long>")
{
    const auto file = matrixFileFullPath("Solvable3x3.txt");
    const auto argc = 5;
    const char* argv[] = {
        "./Runner",
        "-v", "long",
        "-f", file.c_str()
    };
    REQUIRE_NOTHROW(Runner(argc, argv));
    auto runner = Runner(argc, argv);
    REQUIRE_NOTHROW(runner.run());
    REQUIRE(!runner.hasSomethingToRun());
}

TEST_CASE("<Runner><-v><result>")
{
    const auto file = matrixFileFullPath("Solvable3x3.txt");
    const auto argc = 5;
    const char* argv[] = {
        "./Runner",
        "-v", "result",
        "-f", file.c_str()
    };
    REQUIRE_NOTHROW(Runner(argc, argv));
    auto runner = Runner(argc, argv);
    REQUIRE_NOTHROW(runner.run());
    REQUIRE(!runner.hasSomethingToRun());
}
