#include "Graphic.h"

#include <iostream>

using std::cout;

void graphic::Graphic::stop() {
  cout << "Graphic thread was stopped\n";
}

void graphic::Graphic::start() {
  cout << "Graphic thread was started\n";
}
