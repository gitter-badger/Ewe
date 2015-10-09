#ifndef LOGIC_H_
#define LOGIC_H_

#include "Dependencies.h"

#include <ThreadManager.h>

namespace logic {

class Logic : public thread_manager::ThreadSubject {
public:
  void stop();
  void start();
};

}

#endif // LOGIC_H_
