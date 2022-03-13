#include "App.h"
#include <Engine.h>
#include "framework.h"

bool App::Init(HINSTANCE hInstance, int nCmdShow, HACCEL hAccelTable)
{
    _hAccelTable = hAccelTable;

    // Effectue l'initialisation de l'application :
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

	_engine = new Engine(_window, SCREEN_WIDTH, SCREEN_HEIGHT);
}


bool App::Loop()
{
    _running = true;

    while (_running == true)
    {
        HandleInputs();
        UpdateTime();
        _engine->Update();
        _engine->RenderFrame();
    }
}

void App::UpdateTime() {

    float newSysTime = timeGetTime();
    float elapsedSysTime = newSysTime - m_sysTime;
    if (elapsedSysTime < 0.005f) // 200 fps max
        return false;
    m_sysTime = newSysTime;
    if (elapsedSysTime > 0.04f) // 25 fps min
        elapsedSysTime = 0.04f;

    // App time
    m_elapsedTime = elapsedSysTime;
    m_time += m_elapsedTime;
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
    _engine->CleanD3D();
    delete _engine;
}


bool App::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _hInstance = hInstance; // Stocke le handle d'instance dans la variable globale

    _window = CreateWindowW(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
        CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);


    if (!_window)
    {
        return FALSE;
    }

    ShowWindow(_window, nCmdShow);
    UpdateWindow(_window);

    return TRUE;
}