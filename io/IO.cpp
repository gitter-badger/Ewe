#include "IO.h"

#include <iostream>

using std::cout;

void io::IO::processCommand (command_manager::Command& c) {
  using command_manager::CommandType;
  switch (c.commandType) {
  case CommandType::PAUSE: cout << "IO pause"; break;
  case CommandType::RESUME: cout << "IO resume"; break;
  default: break;
  }
  return;
}

io::IO::IO() { 
  id = command_manager::ID::IO;
}
void io::IO::stop() {
  cout << "IO thread was stopped\n";

  this->willStop = true;
}

void io::IO::start() {
  cout << "IO thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds (100);
    std::this_thread::sleep_for (a);

    processCommands ();
  }
}
