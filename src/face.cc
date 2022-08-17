

#include "face.h"

Face::Face(Texture *t, int map_width, int map_height) {
  t_ = t;
  map_width_ = map_width;
  map_height_ = map_height;
  position_ = glm::vec2(0, 0);
  size_ = glm::vec2(100, 100);
}

void Face::Move(Direction direction) {
  if (direction == Up) {
    if (position_.y != 0) {
      position_.y -= size_.y;
    }
  } else if (direction == Right) {
    if (position_.x + size_.x != map_width_) {
      position_.x += size_.x;
    }
  } else if (direction == Down) {
    if (position_.y + size_.y != map_height_) {
      position_.y += size_.y;
    }
  } else if (direction == Left) {
    if (position_.x != 0) {
      position_.x -= size_.x;
    }
  }
}
