
#include "game.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "face.h"
#include "loader.h"
#include "renderer.h"

GLFWwindow *Game::window_ = nullptr;
std::map<std::string, Texture *> Game::textures;

const int kWidth = 800;
const int kHeight = 600;

Renderer *renderer;
Face *face;

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

  glfwSetKeyCallback(window_, Game::ProcessInput);
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

  glewInit();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // load textures
  // auto t = Loader::loadTexture("assets/background.jpg");
  auto t = Loader::loadTexture("assets/awesomeface.png");

  std::string key = "t1";
  textures[key] = t;

  // init renderer
  renderer = new Renderer();
  renderer->Init();

  face = new Face(t, kWidth, kHeight);

  // TODO(CC): move inside renderer
  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(kWidth), static_cast<float>(kHeight),
                 0.0f, -1.0f, 1.0f);
  renderer->shader_->SetMatrix4("projection", projection, true);
}

void Game::Run() {
  while (!glfwWindowShouldClose(window_)) {

    // Game::ProcessInput();
    Game::Draw();

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  glfwTerminate();
}

void Game::ProcessInput(GLFWwindow *window, int key, int scancode, int action,
                        int mode) {
  if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window_, true);
  } else if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_PRESS) {
    face->Move(Face::Direction::Up);
  } else if (glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    face->Move(Face::Direction::Right);
  } else if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS) {
    face->Move(Face::Direction::Down);
  } else if (glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS) {
    face->Move(Face::Direction::Left);
  }
}

void Game::Draw() {
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  renderer->Draw(face->t_, face->position_, face->size_);
}