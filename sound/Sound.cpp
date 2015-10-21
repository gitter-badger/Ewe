#include "Sound.h"

#include <iostream>

using std::cout;

sound::Sound::Sound() {
  id = command_manager::ID::SOUND;
}

void sound::Sound::processCommand (command_manager::Command& c) {
  using command_manager::CommandType;
  switch (c.commandType) {
  case CommandType::PAUSE: cout << "Sound pause"; break;
  case CommandType::RESUME: cout << "Sound resume"; break;
  default: break;
  }
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

    processCommands ();
  }
}
