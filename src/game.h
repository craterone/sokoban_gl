#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <map>
#include <string>
#include <thread>
#include <memory>

#include "texture.h"
#include "thread_queue.h"

class Game {
public:
  Game();

  static void Init();
  static void Run();

  static void Draw();
  static void ProcessInput(std::string direction);

  static std::map<std::string, Texture *> textures;
  static std::unique_ptr<std::thread> thread_;
  
  static ThreadQueue *q_ ;

};
#endif /* SRC_GAME_H_ */
