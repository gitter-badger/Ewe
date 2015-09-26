#include <vector>
#include <memory>
#include <thread>
#include <algorithm>

#include <Command.h>

namespace thread_manager {

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::thread;
using std::for_each;

using patterns::MethodExecuteCommand;
using patterns::Command;

class ThreadSubject {
public:
  virtual void stop() = 0;
  virtual void start() = 0;
};

class ThreadCommand : public MethodExecuteCommand<ThreadSubject> {
public:
  ThreadCommand(shared_ptr<ThreadSubject> s)
    : MethodExecuteCommand<ThreadSubject>(s, &ThreadSubject::start) {};
  void stop();
};

class ThreadManager {
private:
  vector<ThreadCommand> threads;
public:
  void start();
  void stop();
};
}