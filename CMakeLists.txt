# general

cmake_minimum_required(VERSION 3.12)

project(NPuzzle)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# npuzzle library

set(NPuzzleDir ${CMAKE_CURRENT_SOURCE_DIR}/NPuzzleSources)

file(GLOB NPuzzleSources	${NPuzzleDir}/Set.hpp
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
	 			${NPuzzleDir}/Queue.hpp
	 			${NPuzzleDir}/Matrix.hpp
	 			${NPuzzleDir}/Move.hpp
)

add_library(NPuzzle STATIC ${NPuzzleSources})

# Tester library

set(TesterDir ${CMAKE_CURRENT_SOURCE_DIR}/TesterSources)

file(GLOB TesterSources		${TesterDir}/Tester.hpp
				${TesterDir}/Tester.cpp
)

add_library(Tester STATIC ${TesterSources})

target_include_directories(Tester PUBLIC ${NPuzzleDir})

# Run executable

set(RunnerDir ${CMAKE_CURRENT_SOURCE_DIR}/NPuzzleRunner)
file(GLOB NPuzzleRunnerSources ${RunnerDir}/main.cpp)

add_executable(Run ${NPuzzleRunnerSources})

target_link_libraries(Run NPuzzle)

target_include_directories(Run PUBLIC ${NPuzzleDir})

# RunTests executable

set(TestsRunnerDir ${CMAKE_CURRENT_SOURCE_DIR}/TestsRunner)
file(GLOB TestsRunnerSources ${TestsRunnerDir}/main.cpp)

add_executable(RunTests ${TestsRunnerSources})

target_link_libraries(RunTests NPuzzle Tester)

target_include_directories(RunTests PUBLIC ${NPuzzleDir} ${TesterDir})

# RunUnitTests executable

set(UnitTestsDir ${CMAKE_CURRENT_SOURCE_DIR}/UnitTests)
file(GLOB UnitTestsSources      ${UnitTestsDir}/main.cpp
        			${UnitTestsDir}/Utils.cpp
        			${UnitTestsDir}/Solver.cpp
)

add_executable(RunUnitTests ${UnitTestsSources})

target_link_libraries(RunUnitTests NPuzzle Tester)

target_include_directories(RunUnitTests PUBLIC ${NPuzzleDir} ${TesterDir})
