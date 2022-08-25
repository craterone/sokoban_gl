#ifndef SRC_THREAD_QUEUE_H_
#define SRC_THREAD_QUEUE_H_


#include <deque>
#include <mutex>
#include <memory>
#include <condition_variable>

class Chunk {
 public:
  Chunk(int width, int height, int id);
  ~Chunk();
  int id_;
  int width_;
  int height_;
  int length_;
  char* data_ = nullptr;
};

class ThreadQueue {
 public:
  ThreadQueue();

  void pushPacket(std::shared_ptr<Chunk>& chunk);
  std::shared_ptr<Chunk> popPacket();

  std::mutex queue_mutex_;
  std::condition_variable queue_cond_;

  std::deque<std::shared_ptr<Chunk>> queue_;
};

#endif /* SRC_THREAD_QUEUE_H_ */
