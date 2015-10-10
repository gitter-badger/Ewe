#ifndef COMMAND_MANAGER_H_
#define COMMAND_MANAGER_H_

#include <map>
#include <memory>
#include <queue>

namespace command_manager {
  enum ID {
    GRAPHIC,
    IO,
    LOGIC,
    SOUND,
    THREAD_MANAGER
  };

  enum CommandType {
    KILL,
    PAUSE,
    ACTION,
    PLAY
  };

  class Command {
  public:
    ID from, to;
    CommandType commandType;
    int args [3];
  };

  class CommandManager {
    std::map<ID, std::shared_ptr<std::queue<Command>>> queues_;
    std::queue<Command> commands_;
  public:
    void addQueue (ID, std::shared_ptr<std::queue<Command>>);
    void push (Command&);
    void process ( );
  };
}

#endif // COMMAND_MANAGER_H_