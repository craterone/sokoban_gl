#ifndef SRC_FACE_H_
#define SRC_FACE_H_

#include <glm/glm.hpp>

#include "texture.h"

class Face {
public:
  Face(Texture *t, int map_width, int map_height);
  enum Direction { Up = 0, Right, Down, Left };
  void Move(Direction direction);

  int map_width_;
  int map_height_;

  glm::vec2 position_;
  glm::vec2 size_;
  Texture *t_;
};
#endif /* SRC_FACE_H_ */
