#include "Graphic.h"

#include <iostream>

using std::cout;

std::shared_ptr<data::Object> graphic::Graphic::getObjectByTraceRay(int, int) {
  return std::shared_ptr<data::Object>();
}

void graphic::Graphic::pushTask(std::shared_ptr<GraphicTask> task) {}

void graphic::Graphic::stop() {
  cout << "Graphic thread was stopped\n";
}

void graphic::Graphic::start() {
  cout << "Graphic thread was started\n";
}
