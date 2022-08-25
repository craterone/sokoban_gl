
#include "loader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GLES3/gl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader *Loader::loadShader(const char *vShaderFile, const char *fShaderFile) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try {
    // open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

  } catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  const char *gShaderCode = geometryCode.c_str();
  // 2. now create shader object from source code
  auto shader = new Shader();
  shader->Compile(vShaderCode, fShaderCode, nullptr);
  return shader;
}

Texture *Loader::loadTexture(const char *file) {
  auto texture = new Texture();
  // TODO(CC): may add rgba
  // if (false) {

  // }
  texture->Internal_Format = GL_RGBA;
  texture->Image_Format = GL_RGBA;
  // load image
  int width, height, nrChannels;
  unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
  // now generate texture
  texture->Generate(width, height, data);
  // and finally free image data
  stbi_image_free(data);

  return texture;
}