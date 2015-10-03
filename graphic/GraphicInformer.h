#ifndef GRAPHIC_INFORMER_H_
#define GRAPHIC_INFORMER_H_

#include <memory>
#include <queue>

#include <GraphicData.h>

#include "Graphic.h"

namespace graphic {

class GraphicInformer : private Graphic {
public:
  using Graphic::getObjectByTraceRay;

  GraphicInformer(const Graphic&);
};

}

#endif // GRAPHIC_INFORMER_H_
