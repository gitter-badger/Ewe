#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include <vector>
#include <thread>

namespace thread_manager {

class ThreadSubject {
public:
  virtual void stop() = 0;
  virtual void start() = 0;
};

class ThreadManager {
private:
  std::vector<ThreadSubject*> commands_;
  std::vector<std::thread> threads_;
public:
  void add(ThreadSubject *);
  void start();
  void stop();
};

}

#endif // THREAD_MANAGER_H_
