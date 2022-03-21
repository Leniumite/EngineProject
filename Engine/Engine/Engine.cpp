#include "pch.h"
#include "framework.h"
#include <strsafe.h>


#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)


void Engine::Init(HWND window, int screenWidth, int screenHeight)
{
	_currentWindow = window;
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;


    _timer = new STimer();
    _timer->init_SystemTime();

    InitD3D();
    Component::Init();
}

void Engine::Update()
{
    _MM.CalculateDelta();
    _MM.GetMousePosition();
    
    for (GameObject* go : _currentScene->_gameObjectList)
    {
        go->UpdateComponents();
    }
}


void Engine::InitD3D()
{
    _d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = _currentWindow;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = _screenWidth;
    d3dpp.BackBufferHeight = _screenHeight;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    _d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _currentWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &_d3ddev);

    //InitGraphics();
    InitLights();

    _d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
    _d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    _d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    _d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

}

void Engine::InitLights()
{
    D3DLIGHT9 blueLight; // create the light struct
    D3DLIGHT9 redLight;
    D3DLIGHT9 whiteLight;
    D3DMATERIAL9 material; //create the material struct

    ZeroMemory(&blueLight, sizeof(blueLight));    // clear out the light struct for use
    blueLight.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    blueLight.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);    // set the light's color
    blueLight.Direction.x = -1.0f; //Ouais c'est pas beau, mais pas de conversion possible entre un D3DVECTOR et D3DXVECTOR3
    blueLight.Direction.y = 0.0f;
    blueLight.Direction.z = 0.0f;

    _d3ddev->SetLight(0, &blueLight);    // send the light struct properties to light #0
    _d3ddev->LightEnable(0, TRUE);    // turn on light #0

    ZeroMemory(&redLight, sizeof(redLight));    // clear out the light struct for use
    redLight.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    redLight.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);    // set the light's color
    redLight.Direction.x = 1.0f; //Ouais c'est pas beau, mais pas de conversion possible entre un D3DVECTOR et D3DXVECTOR3
    redLight.Direction.y = 0.0f;
    redLight.Direction.z = 0.0f;

    _d3ddev->SetLight(1, &redLight);    // send the light struct properties to light #0
    _d3ddev->LightEnable(1, TRUE);    // turn on light #0

    ZeroMemory(&whiteLight, sizeof(whiteLight));    // clear out the light struct for use
    whiteLight.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    whiteLight.Diffuse = D3DXCOLOR(.8f, .8f, .8f, 1.0f);    // set the light's color
    whiteLight.Direction.x = 0.0f; //Ouais c'est pas beau, mais pas de conversion possible entre un D3DVECTOR et D3DXVECTOR3
    whiteLight.Direction.y = 0.0f;
    whiteLight.Direction.z = -1.0f;

    _d3ddev->SetLight(2, &whiteLight);    // send the light struct properties to light #0
    _d3ddev->LightEnable(2, TRUE);    // turn on light #0

    ZeroMemory(&material, sizeof(D3DMATERIAL9));
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    _d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}


void Engine::RenderFrame()
{
    _d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    _d3ddev->BeginScene();

    if (fpsText == NULL) {
        GameObject* fpsTextGO = _currentScene->AddGameObject();
        fpsText = fpsTextGO->AddComponent<TextComponent>();
    }

    for (GameObject* go : _currentScene->_gameObjectList)
    {
        MeshComponent* meshComponent = go->GetComponent<MeshComponent>();
        if (meshComponent != NULL)
        {
            meshComponent->Draw();
        }
    }

    _d3ddev->EndScene();

    _d3ddev->Present(NULL, NULL, NULL, NULL);

}

bool Engine::UpdateTime() {

    float newSysTime = _timer->GetAppTime();
    float elapsedSysTime = newSysTime - _timer->oldtime;
    if (elapsedSysTime < 0.005f) // 200 fps max
        return false;
    _timer->oldtime = newSysTime;
    if (elapsedSysTime > 0.04f) // 25 fps min
        elapsedSysTime = 0.04f;

    // App time
    _timer->deltaTime = elapsedSysTime;
    _timer->time += elapsedSysTime;

    _timer->_counter++;
    _timer->_timeCounterStarted += elapsedSysTime;
    if (_timer->_timeCounterStarted >= 1) {
        _timer->_timeCounterStarted = 0;
        _timer->_previousCounter = _timer->_counter;

        fpsText->_txt = std::to_wstring(_timer->_previousCounter);

        _timer->_counter = 0;
    }

    return true;
}

void Engine::LoadScene(Scene* newScene)
{
    if (_currentScene != NULL)
    {
        for (GameObject* go : _currentScene->_gameObjectList)
        {
            MeshComponent* meshComponent = go->GetComponent<MeshComponent>();
            if (meshComponent != NULL)
            {
                meshComponent->Clean();
            }

            delete go;
        }
    }

    _currentScene = newScene;
}

void Engine::Refresh()
{
    if (UpdateTime()) {
        Update();
        RenderFrame();
    }
}

void Engine::Uninit(void)
{
    delete _timer;
    
    for (GameObject* go : _currentScene->_gameObjectList)
    {
        MeshComponent* meshComponent = go->GetComponent<MeshComponent>();
        if (meshComponent != NULL)
        {
            meshComponent->Clean();
        }
    }

    delete _currentScene;

    _d3ddev->Release();
    _d3d->Release();
}

Scene* Engine::CreateScene() {
    Scene* newScene = new Scene(this);
    newScene->Init();

    return newScene;
}

void Engine::DrawTextString(int x, int y, DWORD color, const char* str)
{

}
