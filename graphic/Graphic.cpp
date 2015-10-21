#include "Graphic.h"

#include <iostream>

#include <CommandManager.h>

using std::cout;

graphic::Graphic::Graphic ( ) {
  id = command_manager::ID::GRAPHIC;
}

void graphic::Graphic::stop() {
  cout << "Graphic thread was stopped\n";

  this->willStop = true;
}

void graphic::Graphic::processCommand (command_manager::Command& c) {
  using command_manager::CommandType;
  switch (c.commandType) { 
  case CommandType::INITIALIZE: cout << "Graphic init\thwnd = " << c.args[0] << "\n"; break;
  case CommandType::PAUSE: cout << "Graphic pause"; break;
  case CommandType::RESUME: cout << "Graphic resume"; break;
  case CommandType::RESIZE: cout << "Graphic resize\tx = " << c.args[0] << " y = " << c.args[1] << "\n"; break;
  default: break;
  }
  return;
}

void graphic::Graphic::start() {
  cout << "Graphic thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds (100);
    std::this_thread::sleep_for (a);

    processCommands ( );
  }
}
