#include "Graphic.h"

#include <iostream>

#include <CommandManager.h>

using std::cout;

graphic::Graphic::Graphic ( ) {
  this->willStop = false;
}

void graphic::Graphic::stop() {
  cout << "Graphic thread was stopped\n";

  this->willStop = true;
}

void graphic::Graphic::processCommand (command_manager::Command& c) {
  /**
   * Graphic no recieve commands
   */

  return;
}

void graphic::Graphic::start() {
  cout << "Graphic thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds (100);
    std::this_thread::sleep_for (a);

    cout << "Graphic thread was started\n";

    processCommands ( );
  }
}
