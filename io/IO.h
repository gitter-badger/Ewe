#ifndef IO_H_
#define IO_H_

#include "Dependencies.h"

#include <ThreadManager.h>
#include <GraphicInformer.h>

namespace io {

class IO : public thread_manager::ThreadSubject {
  graphic::GraphicInformer graphicInformer;
public:
  void stop();
  void start();
};

}

#endif // IO_H_
