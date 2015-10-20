#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include <vector>
#include <thread>
#include <queue>

#include <CommandManager.h>

namespace thread_manager {

class ThreadSubject {
protected:
  command_manager::CommandManager* commandManager_;

  std::shared_ptr<std::queue<command_manager::Command>> commands_;
  command_manager::ID id;
  void processCommands ( );
  virtual void processCommand (command_manager::Command& c) = 0;

  bool willStop;
public:
  ThreadSubject();

  std::shared_ptr<std::queue<command_manager::Command>> getQueueLink ();
  command_manager::ID getId ( );
  
  virtual void stop ( ) = 0;
  virtual void start ( ) = 0;
  
  void bind(command_manager::CommandManager*);
  // TODO:
  //virtual void pause ( ) = 0;
  //virtual void unpause ( ) = 0;
};

class ThreadManager {
private:
  std::vector<ThreadSubject*> subjects_;
  std::vector<std::thread> threads_;

  command_manager::CommandManager commandManager_;
  std::shared_ptr<std::queue<command_manager::Command>> commands_;
public:
  ThreadManager ( );

  void add(ThreadSubject *);
  void start();
  void stop();

  void listen ( );
};

}

#endif // THREAD_MANAGER_H_
