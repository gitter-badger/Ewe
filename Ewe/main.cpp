#include "Dependencies.h"

#include <ThreadManager.h>

#include <Graphic.h>
#include <Logic.h>
#include <IO.h>
#include <Sound.h>

int main ( ) {
  thread_manager::ThreadManager tm;
  
  graphic::Graphic graphic;
  logic::Logic logic;
  io::IO io;
  sound::Sound sound;

  tm.add(&graphic);
  tm.add(&logic);
  tm.add(&io);
  tm.add(&sound);

  tm.start();

  tm.stop();

  return 0;
}