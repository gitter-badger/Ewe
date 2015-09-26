#include <ThreadManager.h>

namespace graphic {

class Graphic : public thread_manager::ThreadSubject {
public:
  void stop();
  void start();
};

}
