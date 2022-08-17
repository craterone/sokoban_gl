#ifndef SRC_RENDERER_H_
#define SRC_RENDERER_H_

#include "shader.h"
#include "texture.h"

class Renderer {
public:
  Renderer();
  void Init();
  void LoadVertex();
  void Draw(Texture *texture, glm::vec2 position,
            glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

  Shader *shader_;
  unsigned int quadVAO;
};

#endif /* SRC_RENDERER_H_ */
