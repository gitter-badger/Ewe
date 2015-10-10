#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include <vector>
#include <thread>
#include <queue>

#include "CommandManager.h"

namespace thread_manager {

class ThreadSubject {
private:
  std::queue<command_manager::Command> commands_;
  command_manager::ID id;
public:
  std::shared_ptr<std::queue<command_manager::Command>> getQueueLink ();
  command_manager::ID getId ( );
  
  virtual void stop ( ) = 0;
  virtual void start ( ) = 0;

  // TODO:
  //virtual void pause ( ) = 0;
  //virtual void unpause ( ) = 0;
};

class ThreadManager {
private:
  std::vector<ThreadSubject*> subjects_;
  std::vector<std::thread> threads_;

  command_manager::CommandManager commandManager_;
  std::queue<command_manager::Command> commands_;
public:
  ThreadManager ( );

  void push (command_manager::Command);

  void add(ThreadSubject *);
  void start();
  void stop();

  void listen ( );
};

}

#endif // THREAD_MANAGER_H_
