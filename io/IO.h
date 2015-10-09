#ifndef IO_H_
#define IO_H_

#include "Dependencies.h"

#include <ThreadManager.h>

namespace io {

class IO : public thread_manager::ThreadSubject {
public:
  void stop();
  void start();
};

}

#endif // IO_H_
