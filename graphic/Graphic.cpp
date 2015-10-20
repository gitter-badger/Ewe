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
  /**
   * Graphic no recieve commands
   */
  if (c.commandType == command_manager::CommandType::INITIALIZE) cout << "Graphic init\thwnd = " << c.args[0] << "\n";
  if (c.commandType == command_manager::CommandType::PAUSE) cout << "Graphic pause";
  if (c.commandType == command_manager::CommandType::RESUME) cout << "Graphic resume";
  if (c.commandType == command_manager::CommandType::RESIZE) cout << "Graphic resize\tx = " << c.args[0] << " y = " << c.args[1] << "\n";

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
