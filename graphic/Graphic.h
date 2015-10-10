#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <memory>
#include <queue>

#include <ThreadManager.h>
#include <Command.h>

#include "GraphicSupport.h"

namespace graphic {

class GraphicTask : public patterns::Command {

};

class Graphic : public thread_manager::ThreadSubject, private GraphicSupport {
public:
  void stop();
  void start();
};

}

#endif // GRAPHIC_H_
