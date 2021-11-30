cmake_minimum_required(VERSION 3.7)
project(CellularAutomata)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Main.cpp GLAD/src/glad.c EBO.cpp CellularAutomata.cpp ShaderClass.cpp VBO.cpp VAO.cpp)
set(HEADER_FILES CellularAutomata.h EBO.h shader.h shaderClass.h VAO.h VBO.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

include_directories(include)

include_directories(GLAD/include)


file(COPY shaders DESTINATION ${dir}/build)


add_subdirectory(dependencies)

add_executable(CellularAutomata ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(CellularAutomata glfw)
