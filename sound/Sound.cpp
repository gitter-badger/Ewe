#include "Sound.h"

#include <iostream>

using std::cout;

void sound::Sound::stop() {
  cout << "Sound thread was stopped\n";
}

void sound::Sound::start() {
  cout << "Sound thread was started\n";
}
