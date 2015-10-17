#include "Sound.h"

#include <iostream>

using std::cout;

void sound::Sound::processCommand (command_manager::Command& c) {
  return;
}

void sound::Sound::stop() {
  cout << "Sound thread was stopped\n";

  this->willStop = true;
}

void sound::Sound::start() {
  cout << "Sound thread was started\n";

  while (!this->willStop) {
    auto a = std::chrono::milliseconds (100);
    std::this_thread::sleep_for (a);

    cout << "Sound thread was started\n";

    processCommands ();
  }
}
