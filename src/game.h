#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <map>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "texture.h"

class Game {
public:
  Game();

  static void Init();
  static void Run();

  static void Draw();
  static void ProcessInput(GLFWwindow *window, int key, int scancode,
                           int action, int mode);

  static GLFWwindow *window_;
  static std::map<std::string, Texture *> textures;
};
#endif /* SRC_GAME_H_ */
