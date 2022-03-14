#include "App.h"
#include "framework.h"


App::App() {

}

bool App::Init(HINSTANCE hInstance, int nCmdShow, HACCEL hAccelTable)
{
    _hAccelTable = hAccelTable;

    // Effectue l'initialisation de l'application :
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    _sTimer = STimer();
	_engine = Engine();
    _sTimer.init_SystemTime();
    _engine.Init(_window, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void App::Loop()
{
    _running = true;

    while (_running == true)
    {
        HandleInputs();
        UpdateTime();
        _engine.Update();
        _engine.RenderFrame();
    }
}

bool App::UpdateTime() {

    float newSysTime = _sTimer.GetAppTime();
    float elapsedSysTime = newSysTime - _sTimer.oldtime;
    if (elapsedSysTime < 0.005f) // 200 fps max
        return false;
    _sTimer.oldtime = newSysTime;
    if (elapsedSysTime > 0.04f) // 25 fps min
        elapsedSysTime = 0.04f;

    // App time
    _sTimer.deltaTime = elapsedSysTime;
    _sTimer.time += elapsedSysTime;
    return true;
}

void App::HandleInputs() {

    while (PeekMessage(&_msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (!TranslateAccelerator(_msg.hwnd, _hAccelTable, &_msg))
        {
            TranslateMessage(&_msg);
            DispatchMessage(&_msg);
        }
        if (_msg.message == WM_QUIT)
        {
            _running = false;
            break;
        }
    }
}

void App::Uninit()
{
    _engine.CleanD3D();
}


bool App::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _hInstance = hInstance; // Stocke le handle d'instance dans la variable globale

    _window = CreateWindowW(L"ROLLERCOASTER", szTitle, WS_EX_TOPMOST | WS_POPUP,
        CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);


    if (!_window)
    {
        return FALSE;
    }

    ShowWindow(_window, nCmdShow);
    UpdateWindow(_window);

    return TRUE;
}