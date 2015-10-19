#include "TheWindow.h"
#include <string>

static const std::string FullScreenString = "Start fullscreen?";
static const std::string FullScreenProblemString = "FullScreen problem. Start in window?";
static const std::string WndClassName = "windowClass";
static const std::string AppName = "ïèó-ïèó";
static const int WindowWidth = 800;
static const int WindowHeight = 600;
static const bool Windowed = true;
#define BITZ 32

windowFacade::TheWindow::TheWindow() {
  _name = AppName;
  _wndClassName = WndClassName;
  _width = WindowWidth;
  _height = WindowHeight;
  _hwnd = NULL;
  _fullscreen = !Windowed;

  commandProcessors.push_back([](UINT	uMsg, WPARAM	wParam, LPARAM	lParam) {
    if (uMsg == WM_CLOSE) {
      PostQuitMessage(0);
      return true;
    }
    return false;
  });
}
bool windowFacade::TheWindow::_initialize() {
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

  WNDCLASS	wc_;
  wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

  WNDPROC wndproc = [](HWND  hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)->LRESULT __stdcall {
    for (auto p : TheWindow::getInstance().commandProcessors) {
      if (p(uMsg, wParam, lParam))
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  };

  wc_.lpfnWndProc = wndproc;

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
    shutdown();
    //errorMessage = ErrorMessages::windowCreate;
    return false;
  }

  ShowWindow(_hwnd, SW_SHOW);
  SetForegroundWindow(_hwnd);
  SetFocus(_hwnd);

  return true;
}
void windowFacade::TheWindow::shutdown() {
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
windowFacade::TheWindow& windowFacade::TheWindow::getInstance() {
  static windowFacade::TheWindow instance;
  return instance;
}