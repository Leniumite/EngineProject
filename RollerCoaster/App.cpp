#include "framework.h"

float mouseX;
float mouseY;
float offset = 0.0f;

App::App()
{
}

App::~App()
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

    //Préparation du jeu ici

    Scene* _gameScene = _engine.CreateScene();
    _engine.LoadScene(_gameScene);


    LightComponent* whiteLight = _gameScene->AddGameObject()->AddComponent<LightComponent>();
    whiteLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
    whiteLight->SetDirection(D3DXVECTOR3(0.0f, -.5f, 0.0f));
    whiteLight->SetType(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);

    GameObject* cubeGameObject = _gameScene->AddGameObject();
    CubeMeshComponent* cubeComponent = cubeGameObject->AddComponent<CubeMeshComponent>();
    cubeGameObject->AddComponent<TargetListener>();
    cubeGameObject->_transform->ChangePosition(D3DXVECTOR3(0.f, 0.f, -20.f));

    /*GameObject* cubeGameObject2 = _gameScene->AddGameObject();
    CubeMeshComponent* cubeComponent2 = cubeGameObject2->AddComponent<CubeMeshComponent>();
    TargetListener* tList2 = cubeGameObject2->AddComponent<TargetListener>();
    cubeComponent2->SetMaterialColor(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
    cubeGameObject2->_transform->ChangePosition(D3DXVECTOR3(20.f, 0.f, 0.f));
    BoxCollider* boxCollider = cubeGameObject2->AddComponent<BoxCollider>();
    boxCollider->collisionListeners.push_back(tList2);*/

    GameObject* cubeGameObject3 = _gameScene->AddGameObject();
    CubeMeshComponent* cubeComponent3 = cubeGameObject3->AddComponent<CubeMeshComponent>();
    cubeGameObject3->AddComponent<TargetListener>();
    cubeGameObject3->_transform->ChangePosition(D3DXVECTOR3(0.f, 0.f, 20.f));

    GameObject* cubeGameObject4 = _gameScene->AddGameObject();
    CubeMeshComponent* cubeComponent4 = cubeGameObject4->AddComponent<CubeMeshComponent>();
    cubeGameObject4->AddComponent<TargetListener>();
    cubeGameObject4->_transform->ChangePosition(D3DXVECTOR3(-20.f, 0.f, 0.f));

    GameObject* railManager = _gameScene->AddGameObject();
    RailsManager* RM = railManager->AddComponent<RailsManager>();

    GameObject* targetManager = _gameScene->AddGameObject();
    TargetManager* targetManagerComp = targetManager->AddComponent<TargetManager>();

    _player = _gameScene->AddGameObject();
    _player->AddComponent<Player>();

    //GameObject* cGameObject = _gameScene->AddGameObject();
    //CubeMeshComponent* cComponent = cGameObject->AddComponent<CubeMeshComponent>();
    //cGameObject->_transform->ChangePositionX(3.0f);

    GameObject* fpsTextGO = _gameScene->AddGameObject();
    fpsTextGO->AddComponent<FpsText>();

    GameObject* escUIManagerGO = _gameScene->AddGameObject();
    _escUIManager = escUIManagerGO->AddComponent<EscapeUIManager>();

    GameObject* quitButtonGO = _gameScene->AddGameObject();
    ButtonComponent* quitButton = quitButtonGO->AddComponent<ButtonComponent>();
    quitButton->ChangeRect(
        1080 / 2 - 12, 
        1920 / 2 - 45, 
        1080 / 2 + 12, 
        1920 / 2 + 45);
    quitButton->_text->_txt = L"QUIT APP";
    _escUIManager->_uiButtons.push_back(quitButton);
    quitButton->isEnable = FALSE;

    GameObject* quitListenerGO = _gameScene->AddGameObject();
    QuitButton* quitListener = quitListenerGO->AddComponent<QuitButton>();
    quitButton->_listeners.push_back(quitListener);

    PlaySound(L"Ressources\\1-07 Coconut Mall.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //Entrée dans la boucle de jeu ici
    while (_running == true)
    {
        if (HandleInputs() == false)
            break;
        _engine.Refresh();
        _escUIManager->Update();
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
