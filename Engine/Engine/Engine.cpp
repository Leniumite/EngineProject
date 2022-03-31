#include "pch.h"
#include "framework.h"
#include <strsafe.h>


#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)


void Engine::Init(HWND window, int screenWidth, int screenHeight)
{
    srand(time(NULL));
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

    
    if (GetScene()->_mainCamera->isMenuOpen == FALSE) {

        _MM.CalculateDelta();
        _MM.CenterCursor();
        _MM.GetMousePosition();

		_CM.checkCollisions();
       
        for (GameObject* go : _currentScene->_gameObjectList)
        {
            go->UpdateComponents();
        }

    }
    
}


void Engine::InitD3D()
{
    _d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    D3DXMatrixIdentity(&_identityMatrix);

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

    ShowCursor(FALSE);
    _d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _currentWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &_d3ddev);
    _d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
    _d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    _d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    _d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));

}

void Engine::RenderFrame()
{
    _d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    _d3ddev->BeginScene();

    for (GameObject* go : _currentScene->_gameObjectList)
    {
        list<MeshComponent*> meshComponents = go->GetComponentAllComponentsOfType<MeshComponent>();
        for (MeshComponent* meshComponent : meshComponents)
        {
            if (meshComponent != NULL && meshComponent->isEnable == TRUE)
            {
                _d3ddev->SetTransform(D3DTS_WORLD, &go->_transform->matrix);
                meshComponent->Draw();
            }
        }
    }

    _d3ddev->EndScene();

    _d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Engine::DestroyGameobjectWaiting()
{
    for (GameObject* go : objectToDestroy)
    {
        GetScene()->RemoveGameObject(go);
    }
    objectToDestroy.clear();
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
        DestroyGameobjectWaiting();
    }
}

void Engine::Uninit(void)
{
    delete _timer;
    delete _currentScene;

    _d3ddev->Release();
    _d3d->Release();
}

Scene* Engine::CreateScene() {
    Scene* newScene = new Scene(this);
    newScene->Init();

    return newScene;
}

void Engine::Destroy(GameObject* go, float timer)
{
    objectToDestroy.push_back(go);    
}
