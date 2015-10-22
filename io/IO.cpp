#include "IO.h"

#include <iostream>

using std::cout;
static const int ioSleep = 100;

command_manager::ID io::IO::id() {
  return command_manager::ID::IO;
}

io::IO::IO() { 
}
void io::IO::start() {
  cout << "IO thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds(ioSleep);
    std::this_thread::sleep_for(a);

    processCommands();
  }
}
void io::IO::stop() {
  cout << "IO thread was stopped\n";

  this->willStop = true;
}

void io::IO::processCommand(command_manager::Command& c) {
  using command_manager::CommandType;
  switch (c.commandType) {
  case CommandType::PAUSE: cout << "IO pause"; break;
  case CommandType::RESUME: cout << "IO resume"; break;
  default: break;
  }
  return;
}
