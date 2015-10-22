#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <memory>
#include <queue>

#include <ThreadManager.h>

#include "GraphicSupport.h"

namespace graphic {

class Graphic : public thread_manager::ThreadSubject, private GraphicSupport {
  void processCommand (command_manager::Command& c);
public:
  command_manager::ID id();
  void stop();
  void start();

  Graphic ( );
};

}

#endif // GRAPHIC_H_
