#ifndef WINDOW_FACADE_H
#define WINDOW_FACADE_H

#include <ThreadManager.h>
#include <Windows.h>

namespace window_facade {

  class WindowFacade : public thread_manager::ThreadSubject {
    void processCommand(command_manager::Command& c);
  public:
    command_manager::ID id();
    void set(command_manager::Command& c);
    void stop();
    void start();
    static WindowFacade* getInstance();
    void setMinimized(bool);
    bool getMinimized();
    void sendPause();
    void sendResume();
    void sendKill();
    void sendResize(int,int);
    void sendHwnd();

  private:
    WindowFacade();
    WindowFacade(WindowFacade&);
    void _generateCommandProcessors();

  private:
    bool _initialize();
    void _shutdown();

    std::map<UINT, std::function<bool(WPARAM, LPARAM)>> _commandProcessors;
    HWND  _hwnd;
    int   _width;
    int   _height;

    std::string _name;
    std::string _wndClassName;
    bool _fullscreen;
    bool _minimized;
  };

}

#endif // WINDOW_FACADE_H

