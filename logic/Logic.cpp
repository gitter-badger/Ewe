#include "Logic.h"

#include <iostream>

using std::cout;

void logic::Logic::stop() {
  cout << "Logic thread was stopped\n";
}

void logic::Logic::start() {
  cout << "Logic thread was started\n";
}
