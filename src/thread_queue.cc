#include "thread_queue.h"

#include <iostream>

Chunk::Chunk(int width, int height, int id)
    : width_(width), height_(height), id_(id), length_(width * height * 4) {
  data_ = new char[length_];
}

Chunk::~Chunk() { delete[] data_; }

ThreadQueue::ThreadQueue() {}

void ThreadQueue::pushPacket(std::shared_ptr<Chunk> &FramePacket) {
  std::lock_guard<std::mutex> lck(queue_mutex_);

  std::cout << "packet in " << FramePacket->id_ << std::endl;
  queue_.push_back(FramePacket);

  if (queue_.size() == 1)
    queue_cond_.notify_one();
}

std::shared_ptr<Chunk> ThreadQueue::popPacket() {
  std::lock_guard<std::mutex> lck(queue_mutex_);

  std::shared_ptr<Chunk> packet;

  if (!queue_.empty()) {
    packet = queue_.front();
    queue_.pop_front();
    std::cout << "packet out " << packet->id_ << std::endl;
  }

  return packet;
}