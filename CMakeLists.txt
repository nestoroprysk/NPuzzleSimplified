# general

cmake_minimum_required(VERSION 3.12)

project(NPuzzle)

set(CMAKE_CXX_STANDARD 17)

# npuzzle library

set(NPuzzleDir ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

file(GLOB NPuzzleSources	${NPuzzleDir}/IContainer.hpp
							${NPuzzleDir}/Set.hpp
							${NPuzzleDir}/Set.cpp
							${NPuzzleDir}/Queue.hpp
							${NPuzzleDir}/Queue.cpp
							${NPuzzleDir}/Solver.hpp
							${NPuzzleDir}/Solver.cpp
							${NPuzzleDir}/State.hpp
							${NPuzzleDir}/State.cpp
							${NPuzzleDir}/Types.hpp
							${NPuzzleDir}/Utils.hpp
				 			${NPuzzleDir}/Utils.cpp
							${NPuzzleDir}/ContainerCreator.hpp
				 			${NPuzzleDir}/ContainerCreator.cpp
				 			${NPuzzleDir}/HeuristicFunctions.hpp
				 			${NPuzzleDir}/HeuristicFunctions.cpp
)

add_library(NPuzzle STATIC ${NPuzzleSources})

# Runner executable

set(RunnerDir ${CMAKE_CURRENT_SOURCE_DIR}/Main)
file(GLOB MainSources ${RunnerDir}/main.cpp)

add_executable(Runner ${MainSources})

target_link_libraries(Runner NPuzzle)

target_include_directories(Runner PUBLIC ${NPuzzleDir})
