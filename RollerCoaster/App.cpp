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

    InitGame();

    return TRUE;
}


void App::InitGame()
{
    //Préparation du jeu ici

    Scene* _gameScene = _engine.CreateScene();
    _engine.LoadScene(_gameScene);

    _engine.GetScene()->_mainCamera->_gameObject->AddComponent<CameraController>();


    LightComponent* whiteLight = _gameScene->AddGameObject()->AddComponent<LightComponent>();
    whiteLight->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
    whiteLight->SetDirection(D3DXVECTOR3(.5f, -.5f, 0.0f));
    whiteLight->SetType(D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);

    GameObject* railManager = _gameScene->AddGameObject();
    RailsManager* RM = railManager->AddComponent<RailsManager>();

    GameObject* targetManager = _gameScene->AddGameObject();
    TargetManager* targetManagerComp = targetManager->AddComponent<TargetManager>();

    _player = _gameScene->AddGameObject();
    Player* playerComp = _player->AddComponent<Player>();
    playerComp->_ptsText->SetCorners(20, 0, 200, 200);

    GameObject* cGameObject = _gameScene->AddGameObject();
    CubeMeshComponent* cComponent = cGameObject->AddComponent<CubeMeshComponent>();
    cGameObject->_transform->ChangePositionX(3.0f);

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

    //PlaySound(L"Ressources\\1-07 Coconut Mall.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void App::Loop()
{
    _running = true;

    //Entrée dans la boucle de jeu ici
    while (_running == true)
    {
        _engine.Refresh();
        _escUIManager->Update();
    }
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
