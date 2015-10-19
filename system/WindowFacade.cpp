#include "WindowFacade.h"

#include <iostream>
using std::cout;

windowFacade::WindowFacade::WindowFacade() {
  this->willStop = false;
}

void windowFacade::WindowFacade::stop() {
  cout << "WindowFacade thread was stopped\n";

  this->willStop = true;
}
void windowFacade::WindowFacade::processCommand(command_manager::Command& c) {
  /**
  * windowFacade no recieve commands
  */

  return;
}

void windowFacade::WindowFacade::start() {
  cout << "WindowFacade thread was started\n";
  _initialize();
  MSG msg_;

  while (!this->willStop) {
    auto a = std::chrono::milliseconds(300);
    std::this_thread::sleep_for(a);

    cout << "WindowFacade thread working!\n";

    if (PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE)) {
      // TODO: generate sortedSet for messages that need to translate & dispatch!
      
      //if (msg_.message == WM_QUIT) {
      //  this->willStop = false;
      //}
      //else {
        TranslateMessage(&msg_);
        DispatchMessage(&msg_);
      //}
    }

    processCommands();
  }
}
