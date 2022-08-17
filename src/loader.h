#ifndef SRC_LOADER_H_
#define SRC_LOADER_H_

#include "shader.h"
#include "texture.h"

class Loader {
public:
  static Shader *loadShader(const char *vShaderFile, const char *fShaderFile);
  static Texture *loadTexture(const char *file);
};

#endif /* SRC_LOADER_H_ */
