#ifndef WHT_WINDOW_H_
#define WHT_WINDOW_H_

#include <string>
#include <functional>
#include <vector>
#include <Windows.h>

namespace windowFacade {

  class TheWindow {
  public:
    TheWindow();

  protected:
    bool _initialize();
    void shutdown();

    HWND  _hwnd;
    int   _width;
    int   _height;

  private:
    std::vector<std::function<bool(UINT, WPARAM, LPARAM)>> commandProcessors;
    static TheWindow& getInstance();

    std::string _name;
    std::string _wndClassName;
    bool _fullscreen;
  };

}

#endif WHT_WINDOW_H_
