#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include <vector>
#include <memory>
#include <thread>

#include <Command.h>

namespace thread_manager {

using std::vector;
using std::shared_ptr;
using std::thread;

class ThreadSubject {
public:
  virtual void stop() = 0;
  virtual void start() = 0;
};

class ThreadCommand : public patterns::MethodExecuteCommand<ThreadSubject> {
public:
  ThreadCommand(ThreadSubject* s)
    : MethodExecuteCommand<ThreadSubject>(s, &ThreadSubject::start) {};
  void stop();
};

class ThreadManager {
private:
  vector<ThreadCommand*> threads_;
  vector<thread> threads__;
public:
  void add(ThreadCommand *);
  void start();
  void stop();
};

}

#endif // THREAD_MANAGER_H_
