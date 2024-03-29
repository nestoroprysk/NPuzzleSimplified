# General

cmake_minimum_required(VERSION 3.12)

project(NPuzzle)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Npuzzle library

set(NPuzzleDir ${CMAKE_CURRENT_SOURCE_DIR}/NPuzzleSources)

file(GLOB NPuzzleSources    ${NPuzzleDir}/Set.hpp
                            ${NPuzzleDir}/Set.cpp
                            ${NPuzzleDir}/Solver.hpp
                            ${NPuzzleDir}/State.hpp
                            ${NPuzzleDir}/State.cpp
                            ${NPuzzleDir}/Types.hpp
                            ${NPuzzleDir}/Utils.hpp
                            ${NPuzzleDir}/Utils.cpp
                            ${NPuzzleDir}/HeuristicFunctions.hpp
                            ${NPuzzleDir}/HeuristicFunctions.cpp
                            ${NPuzzleDir}/Hash.hpp
                            ${NPuzzleDir}/Hash.cpp
                            ${NPuzzleDir}/Queue.hpp
                            ${NPuzzleDir}/Matrix.hpp
                            ${NPuzzleDir}/Matrix.cpp
                            ${NPuzzleDir}/Move.hpp
                            ${NPuzzleDir}/SolverConfiguration.hpp
                            ${NPuzzleDir}/Comparator.hpp
                            ${NPuzzleDir}/Result.hpp
                            ${NPuzzleDir}/Printer.hpp
                            ${NPuzzleDir}/Parser.hpp
                            ${NPuzzleDir}/Parser.cpp
                            ${NPuzzleDir}/Runner.hpp
                            ${NPuzzleDir}/Runner.cpp
)

add_library(NPuzzle STATIC ${NPuzzleSources})

# Run executable

set(RunnerDir ${CMAKE_CURRENT_SOURCE_DIR}/NPuzzleRunner)
file(GLOB NPuzzleRunnerSources ${RunnerDir}/main.cpp)

add_executable(Run ${NPuzzleRunnerSources})

target_link_libraries(Run NPuzzle)

target_include_directories(Run PUBLIC ${NPuzzleDir})

# RunUnitTests executable

set(UnitTestsDir ${CMAKE_CURRENT_SOURCE_DIR}/UnitTests)
file(GLOB UnitTestsSources      ${UnitTestsDir}/main.cpp
                                ${UnitTestsDir}/Utils.cpp
                                ${UnitTestsDir}/Parser.cpp
                                ${UnitTestsDir}/Solver.cpp
                                ${UnitTestsDir}/Runner.cpp
)

add_executable(RunUnitTests ${UnitTestsSources})

target_link_libraries(RunUnitTests NPuzzle)

target_include_directories(RunUnitTests PUBLIC ${NPuzzleDir})

# Definitions

add_definitions(-DPATH_TO_UNIT_TESTS_DIR="${UnitTestsDir}")
