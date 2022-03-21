#include "pch.h"
#include "framework.h"
#include <strsafe.h>


#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

LPD3DXMESH g_pMesh = NULL;
D3DMATERIAL9* g_pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL;
DWORD g_dwNumMaterials = 0L;

void Engine::Init(HWND window, int screenWidth, int screenHeight)
{
	_currentWindow = window;
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;


    _timer = new STimer();
    _timer->init_SystemTime();

    InitD3D();
    InitGeometry();
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

HRESULT Engine::InitGeometry()
{
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    D3DXLoadMeshFromX(L"Ressources\\Tiger.x", D3DXMESH_SYSTEMMEM, _d3ddev, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh);

    // We need to extract the material properties and texture names from the
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if (g_pMeshMaterials == NULL)
        return E_OUTOFMEMORY;
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if (g_pMeshTextures == NULL)
        return E_OUTOFMEMORY;

    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

        g_pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the texture
            D3DXCreateTextureFromFileA(_d3ddev, d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i]);
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
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

    // Meshes are divided into subsets, one for each material. Render them in
    // a loop
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        _d3ddev->SetMaterial(&g_pMeshMaterials[i]);
        _d3ddev->SetTexture(0, g_pMeshTextures[i]);

        // Draw the mesh subset
        g_pMesh->DrawSubset(i);
    }

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
    if (g_pMeshMaterials != NULL)
        delete[] g_pMeshMaterials;

    if (g_pMeshTextures)
    {
        for (DWORD i = 0; i < g_dwNumMaterials; i++)
        {
            if (g_pMeshTextures[i])
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
    if (g_pMesh != NULL)
        g_pMesh->Release();

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
