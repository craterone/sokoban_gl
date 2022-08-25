
#include "game.h"

#include <chrono>
#include <iostream>

#include <EGL/egl.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <strings.h>
#include <thread>

#include "face.h"
#include "loader.h"
#include "renderer.h"
#include "thread_queue.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::map<std::string, Texture *> Game::textures;
std::unique_ptr<std::thread> Game::thread_;
ThreadQueue *Game::q_;

const int kWidth = 640;
const int kHeight = 480;

Renderer *renderer;
Face *face;
char *rgb_data_;
// void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//   // make sure the viewport matches the new window dimensions; note that
//   width
//   // and height will be significantly larger than specified on retina
//   displays. glViewport(0, 0, width, height);
// }

static const int pbufferWidth = kWidth;
static const int pbufferHeight = kHeight;

static const EGLint configAttribs[] = { //
    EGL_SURFACE_TYPE,
    EGL_PBUFFER_BIT,
    EGL_BLUE_SIZE,
    8,
    EGL_GREEN_SIZE,
    8,
    EGL_RED_SIZE,
    8,
    EGL_DEPTH_SIZE,
    8,
    EGL_RENDERABLE_TYPE,
    EGL_OPENGL_BIT,
    EGL_NONE};

static const EGLint pbufferAttribs[] = {
    EGL_WIDTH, pbufferWidth, EGL_HEIGHT, pbufferHeight, EGL_NONE,
};

Game::Game() {}

EGLDisplay eglDpy;
EGLint major, minor;

// 2. Select an appropriate configuration
EGLint numConfigs;
EGLConfig eglCfg;
EGLSurface eglSurf;
EGLContext eglCtx;

void Game::Init() {
  q_ = new ThreadQueue();
  thread_ = std::make_unique<std::thread>([]() {
    rgb_data_ = new char[kWidth * kHeight * 4];
    eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(eglDpy, &major, &minor);

    eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

    // 3. Create a surface
    eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg, pbufferAttribs);

    // 4. Bind the API
    eglBindAPI(EGL_OPENGL_API);

    // 5. Create a context and make it current
    eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT, NULL);

    eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // load textures
    // auto t = Loader::loadTexture("assets/background.jpg");
    auto t = Loader::loadTexture("/root/sokoban_gl/assets/awesomeface.png");

    std::string key = "t1";
    textures[key] = t;

    // init renderer
    renderer = new Renderer();
    renderer->Init();

    face = new Face(t, kWidth, kHeight);

    // TODO(CC): move inside renderer
    glm::mat4 projection =
        glm::ortho(0.0f, static_cast<float>(kWidth),
                   static_cast<float>(kHeight), 0.0f, -1.0f, 1.0f);
    renderer->shader_->SetMatrix4("projection", projection, true);

    // glReadPixels(0, 0, kWidth, kHeight, GL_RGBA, GL_UNSIGNED_BYTE,
    // rgb_data_);

    // // stbi_write_png("/root/webrtc-streamer/1.png", kWidth,
    // stbi_write_png("/root/sokoban_gl/0.png", kWidth, kHeight, 4,
    //                (unsigned char *)rgb_data_, kWidth * 4);

    // bzero(rgb_data_, kWidth * kHeight * 4);

    while (true) {
      Game::Draw();

      std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
  });
}

void Game::ProcessInput(std::string direction) {
  if (direction == "up") {
    face->Move(Face::Direction::Up);
  } else if (direction == "right") {
    face->Move(Face::Direction::Right);
  } else if (direction == "down") {
    face->Move(Face::Direction::Down);
  } else if ("left") {
    face->Move(Face::Direction::Left);
  }
}
int i = 0;
void Game::Draw() {
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  renderer->Draw(face->t_, face->position_, face->size_);

  auto c = std::make_shared<Chunk>(kWidth, kHeight,i);

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, kWidth, kHeight, GL_RGBA, GL_UNSIGNED_BYTE, c->data_);

  // stbi_write_png("/root/sokoban_gl/0.png", kWidth, kHeight, 4,
  //                (unsigned char *)c->data_, kWidth * 4);

  q_->pushPacket(c);

  i++;
}