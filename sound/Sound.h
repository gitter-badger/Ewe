#ifndef SOUND_H_
#define SOUND_H_

#include "Dependencies.h"

#include <ThreadManager.h>

namespace sound {

class Sound : public thread_manager::ThreadSubject {
  void processCommand (command_manager::Command& c);
public:
  void stop();
  void start();
};

}

#endif // SOUND_H_
