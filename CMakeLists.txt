cmake_minimum_required(VERSION 3.5)
project(sokoban)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(THIRD_PARTY_PATH ${PROJECT_SOURCE_DIR}/third_party)

# pkg_check_modules(GLEW REQUIRED IMPORTED_TARGET glew)
# pkg_check_modules(GLM REQUIRED IMPORTED_TARGET glm)



file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_library(${PROJECT_NAME} SHARED
${SOURCES_FILES} 
# stb_test.cc
)
# add_executable(${PROJECT_NAME}
# ${SOURCES_FILES} 
# main.cc
# # stb_test.cc
# )

target_include_directories(${PROJECT_NAME} PUBLIC 
${SRC_PATH}
${THIRD_PARTY_PATH})

target_link_libraries(${PROJECT_NAME} PUBLIC 
  # PkgConfig::GLEW
  # PkgConfig::GLM
  pthread
  OpenGL::EGL
  OpenGL::GL)