#include "IO.h"

#include <iostream>

using std::cout;

void io::IO::stop() {
  cout << "IO thread was stopped\n";
}

void io::IO::start() {
  cout << "IO thread was started\n";
}
