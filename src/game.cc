
#include "game.h"

#include <iostream>

GLFWwindow *Game::window_ = nullptr;

const int kWidth = 640;
const int kHeight = 400;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

Game::Game() {}
void Game::Init() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window_ = glfwCreateWindow(kWidth, kHeight, "Sokoban", NULL, NULL);
  if (window_ == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window_);
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

  glewInit();
}

void Game::Run() {
  while (!glfwWindowShouldClose(window_)) {

    Game::ProcessInput();
    Game::Draw();

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  glfwTerminate();
}

void Game::ProcessInput() {
  if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window_, true);
  }
}

void Game::Draw() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}