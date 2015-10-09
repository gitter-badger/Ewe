#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <memory>
#include <queue>

#include "Dependencies.h"

#include <ThreadManager.h>
#include <Command.h>
#include <GraphicData.h>

namespace graphic {

class GraphicTask : public patterns::Command {

};

class Graphic : public thread_manager::ThreadSubject {
private:
  std::queue<std::shared_ptr<GraphicTask>> taskQueue;
protected:

#pragma region GraphicInformer interface
  std::shared_ptr<data::Object> getObjectByTraceRay(int, int);
#pragma endregion

#pragma region GraphicQueue interface
  void pushTask (std::shared_ptr<GraphicTask>);
#pragma endregion

public:
  void stop();
  void start();


};

}

#endif // GRAPHIC_H_
