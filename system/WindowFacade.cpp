#include "WindowFacade.h"

#include <CommandManager.h>
#include <iostream>
using std::cout;

static const std::string FullScreenString = "Start fullscreen?";
static const std::string FullScreenProblemString = "FullScreen problem. Start in window?";
static const std::string WndClassName = "windowClass";
static const std::string AppName = "ïèó-ïèó";
static const int WindowWidth = 800;
static const int WindowHeight = 600;
static const bool Windowed = true;
#define BITZ 32

window_facade::WindowFacade* window_facade::WindowFacade::getInstance() {
  static WindowFacade* facade = new WindowFacade();
  return facade;
}
window_facade::WindowFacade::WindowFacade() {
  id = command_manager::ID::WINDOW_FACADE;
  _name = AppName;
  _wndClassName = WndClassName;
  _width = WindowWidth;
  _height = WindowHeight;
  _hwnd = NULL;
  _fullscreen = !Windowed;
}
void window_facade::WindowFacade::set(command_manager::Command& c) {
  commandManager_->push(c);
}
void window_facade::WindowFacade::stop() {
  cout << "WindowFacade thread was stopped\n";

  _shutdown();
  this->willStop = true;
}
void window_facade::WindowFacade::processCommand(command_manager::Command& c) {
  /**
  * windowFacade no recieve commands
  */

  return;
}
void window_facade::WindowFacade::start() {
  cout << "WindowFacade thread was started\n";
  getInstance()->_generateCommandProcessors();
  if (!_initialize()) {
    command_manager::Command cmd = command_manager::Command(
      command_manager::ID::WINDOW_FACADE, command_manager::ID::THREAD_MANAGER,
      command_manager::CommandType::KILL);
    set(cmd);
    return;
  }
  command_manager::Command hwndToGraphic = command_manager::Command(
    command_manager::ID::WINDOW_FACADE, command_manager::ID::GRAPHIC,
    command_manager::CommandType::INITIALIZE);
  hwndToGraphic.args[0] = reinterpret_cast<int>(_hwnd);
  set(hwndToGraphic);
  
  command_manager::Command hwndToIO = command_manager::Command(
    command_manager::ID::WINDOW_FACADE, command_manager::ID::IO,
    command_manager::CommandType::INITIALIZE);
  hwndToIO.args[0] = reinterpret_cast<int>(_hwnd);
  set(hwndToIO);

  MSG msg_;

  while (!this->willStop) {
    auto a = std::chrono::milliseconds(100);
    std::this_thread::sleep_for(a);

    cout << "WindowFacade thread working!\n";

    if (PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg_);
      DispatchMessage(&msg_);
    }
    processCommands();
  }
}
void window_facade::WindowFacade::_generateCommandProcessors() {
  _commandProcessors[WM_CLOSE] = [](WPARAM	wParam, LPARAM	lParam) {
    command_manager::Command cmd = command_manager::Command(
        command_manager::ID::WINDOW_FACADE,
        command_manager::ID::THREAD_MANAGER,
        command_manager::CommandType::KILL);
      WindowFacade::getInstance()->set(cmd);
  };
}
bool window_facade::WindowFacade::_initialize() {
  HINSTANCE hInstance_ = GetModuleHandle(NULL);

  DWORD		dwExStyle_;
  DWORD		dwStyle_;
  RECT		windowRect_;

  if (!Windowed) {
    if (MessageBox(NULL, FullScreenString.c_str(), FullScreenString.c_str(), MB_YESNO | MB_ICONQUESTION) == IDYES) {
      _fullscreen = true;
      HDC hDC_ = GetDC(NULL);
      _width = GetDeviceCaps(hDC_, HORZRES);
      _height = GetDeviceCaps(hDC_, VERTRES);
      ReleaseDC(NULL, hDC_);
    }
  }

  windowRect_.left = (long)0;
  windowRect_.right = (long)_width;
  windowRect_.top = (long)0;
  windowRect_.bottom = (long)_height;

  WNDPROC wndproc_ = [](HWND  hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)->LRESULT {
    auto& cp = window_facade::WindowFacade::getInstance()->_commandProcessors;
    auto& it = cp.find(uMsg);
    if (it != cp.end()) {
      it->second(wParam, lParam);
      return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  };

  WNDCLASS	wc_;
  wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc_.lpfnWndProc = wndproc_;
  wc_.cbClsExtra = 0;
  wc_.cbWndExtra = 0;
  wc_.hInstance = hInstance_;
  wc_.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc_.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc_.hbrBackground = NULL;
  wc_.lpszMenuName = NULL;
  wc_.lpszClassName = _wndClassName.c_str();

  if (!RegisterClass(&wc_)) {
    //errorMessage = ErrorMessages::registerWindowClass;
    return false;
  }
  if (_fullscreen) {
    DEVMODE dmScreenSettings_;
    memset(&dmScreenSettings_, 0, sizeof(dmScreenSettings_));
    dmScreenSettings_.dmSize = sizeof(dmScreenSettings_);
    dmScreenSettings_.dmPelsWidth = _width;
    dmScreenSettings_.dmPelsHeight = _height;
    dmScreenSettings_.dmBitsPerPel = BITZ;
    dmScreenSettings_.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
    if (ChangeDisplaySettings(&dmScreenSettings_, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
      if (MessageBox(NULL, FullScreenProblemString.c_str(), FullScreenProblemString.c_str(), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
        _fullscreen = false;
        _width = WindowWidth;
        _height = WindowHeight;
        windowRect_.right = (long)_width;
        windowRect_.bottom = (long)_height;
      }
      else {
        //errorMessage = ErrorMessages::programClose;
        return false;
      }
    }
  }
  if (_fullscreen) {
    dwExStyle_ = WS_EX_APPWINDOW;
    dwStyle_ = WS_POPUP;
    ShowCursor(FALSE);
  }
  else {
    dwExStyle_ = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle_ = WS_OVERLAPPEDWINDOW;
  }
  AdjustWindowRectEx(&windowRect_, dwStyle_, FALSE, dwExStyle_);
  if (!(_hwnd = CreateWindowEx(dwExStyle_,
    _wndClassName.c_str(),
    _name.c_str(),
    dwStyle_ |
    WS_CLIPSIBLINGS |
    WS_CLIPCHILDREN,
    0, 0,
    windowRect_.right - windowRect_.left,
    windowRect_.bottom - windowRect_.top,
    NULL,
    NULL,
    hInstance_,
    NULL))) {
    _shutdown();
    //errorMessage = ErrorMessages::windowCreate;
    return false;
  }

  ShowWindow(_hwnd, SW_SHOW);
  SetForegroundWindow(_hwnd);
  SetFocus(_hwnd);

  return true;
}
void window_facade::WindowFacade::_shutdown() {
  if (_fullscreen) {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(false);
  }
  if (_hwnd && !DestroyWindow(_hwnd)) {
    //MessageBox(NULL, ErrorMessages::realeseHWND.c_str(), ErrorMessages::default.c_str(), MB_OK | MB_ICONINFORMATION);
    _hwnd = NULL;
  }
  if (!UnregisterClass(_wndClassName.c_str(), GetModuleHandle(NULL))) {
    //MessageBox(NULL, ErrorMessages::unregisterClass.c_str(), ErrorMessages::default.c_str(), MB_OK | MB_ICONINFORMATION);
  }
}