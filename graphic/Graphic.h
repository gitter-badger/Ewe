#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <ThreadManager.h>

namespace graphic {

class Graphic : public thread_manager::ThreadSubject {
public:
  void stop();
  void start();
};

}

#endif // GRAPHIC_H_
