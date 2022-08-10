cmake_minimum_required(VERSION 3.5)
project(sokokan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)
pkg_check_modules(GLEW REQUIRED IMPORTED_TARGET glew)
pkg_check_modules(GLM REQUIRED IMPORTED_TARGET glm)



file(GLOB_RECURSE SOURCES_FILES ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES_FILES} main.cc)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/third_party)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  PkgConfig::GLFW3 
  PkgConfig::GLEW
  PkgConfig::GLM
  OpenGL::GL)