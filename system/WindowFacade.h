#ifndef WINDOW_FACADE_H
#define WINDOW_FACADE_H

#include <ThreadManager.h>
#include "TheWindow.h"

namespace windowFacade {

  class WindowFacade : public thread_manager::ThreadSubject, public TheWindow {
    void processCommand(command_manager::Command& c);
  public:
    void stop();
    void start();
  
    WindowFacade();
  };

}

#endif // WINDOW_FACADE_H

