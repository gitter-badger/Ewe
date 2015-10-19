#include "Dependencies.h"

#include <ThreadManager.h>

#include <WindowFacade.h>
#include <Graphic.h>
#include <Logic.h>
#include <IO.h>
#include <Sound.h>

int main ( ) {
  thread_manager::ThreadManager tm;
  
  windowFacade::WindowFacade window;
  graphic::Graphic graphic;
  logic::Logic logic;
  io::IO io;
  sound::Sound sound;
  
  tm.add(&window);
  tm.add(&graphic);
  tm.add(&logic);
  tm.add(&io);
  tm.add(&sound);

  tm.start();

  tm.listen ( );

  getchar ();

  tm.stop ( );

  getchar ();

  return 0;
}