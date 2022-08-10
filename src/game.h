#ifndef SRC_GAME_H_
#define SRC_GAME_H_

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Game {
public:
  Game();

  static void Init();
  static void Run();

  static void Draw();
  static void ProcessInput();

  static GLFWwindow *window_;
};
#endif /* SRC_GAME_H_ */
