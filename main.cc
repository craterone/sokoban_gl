
#include "game.h"

int main() {
  Game::Init();
  Game::thread_->join();
  return 0;
}