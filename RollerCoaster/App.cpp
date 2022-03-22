#include "framework.h"


float mouseX;
float mouseY;

App::App()
{

}

bool App::Init(HINSTANCE hInstance, int nCmdShow, HACCEL hAccelTable)
{
    _hAccelTable = hAccelTable;

    // Effectue l'initialisation de l'application�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    _engine.Init(_window, SCREEN_WIDTH, SCREEN_HEIGHT);
    return TRUE;
}


void App::Loop()
{
    _running = true;

    Scene* _gameScene = _engine.CreateScene();
    //GameObject* cubeGameObject = _gameScene->AddGameObject();
    //CubeMeshComponent* cubeComponent = cubeGameObject->AddComponent<CubeMeshComponent>();

    //GameObject* tigerGameObject = _gameScene->AddGameObject();
    //tigerGameObject->_transform->ChangePositionX(10.0f);
    //PolygonMeshComponent* tigerMeshComponent = tigerGameObject->AddComponent<PolygonMeshComponent>();
    //tigerMeshComponent->SetMeshModel(L"Ressources\\tiger.x");

    //GameObject* cGameObject = _gameScene->AddGameObject();
    //CubeMeshComponent* cComponent = cGameObject->AddComponent<CubeMeshComponent>();
    //cGameObject->_transform->ChangePositionX(3.0f);

    //GameObject* fpsTextGO = _gameScene->AddGameObject();
    //TextComponent* fpsText = fpsTextGO->AddComponent<TextComponent>();
    //fpsText->SetCorners(10, 10, 100, 100);

    _engine.LoadScene(_gameScene);

    while (_running == true)
    {
        if (HandleInputs() == false)
            break;
        _engine.Refresh();
    }

}

bool App::HandleInputs() {

    //GetAsyncKeyState(VK_DOWN) < 0;

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
            return false;
        }
    }
    return true;
}




void App::Uninit()
{
    _engine.Uninit();
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
