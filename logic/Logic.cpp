#include "Logic.h"

#include <iostream>

using std::cout;

void logic::Logic::processCommand (command_manager::Command& c) {
  return;
}

void logic::Logic::stop() {
  cout << "Logic thread was stopped\n";

  this->willStop = true;
}

void logic::Logic::start() {
  cout << "Logic thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds (100);
    std::this_thread::sleep_for (a);

    cout << "Logic thread was started\n";

    processCommands ();
  }
}
