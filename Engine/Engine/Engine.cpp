// Engine.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"


#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)


void Engine::Init(HWND window, int screenWidth, int screenHeight)
{
	_currentWindow = window;
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;


    _timer = new STimer();
    _timer->init_SystemTime();


    Component::Init();
    InitD3D();
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

    _d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _currentWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &_d3ddev);

    //InitGraphics();
    InitLights();

    _d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
    _d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    _d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    _d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

    // select which vertex format we are using
    _d3ddev->SetFVF(CUSTOMFVF);

}

void Engine::InitGraphics()
{
    VOID* pVoid;




    //CUBE VERTEX BUFFER

    CUSTOMVERTEX vertices[] =
    {
        { -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },    // side 1
        { 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },    // side 2
        { -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },

        { -3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },    // side 3
        { -3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },    // side 4
        { 3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },
        { -3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },

        { 3.0f, -3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },    // side 5
        { 3.0f, 3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },    // side 6
        { -3.0f, -3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
    };

    // create a vertex buffer interface called v_buffer
    _d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &_vertexBuffer,
        NULL);


    _vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    _vertexBuffer->Unlock();

    //LIGHTED CUBE INDEX BUFFER

    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 5, 6,    // side 2
        6, 5, 7,
        8, 9, 10,    // side 3
        10, 9, 11,
        12, 13, 14,    // side 4
        14, 13, 15,
        16, 17, 18,    // side 5
        18, 17, 19,
        20, 21, 22,    // side 6
        22, 21, 23,
    };

    _d3ddev->CreateIndexBuffer(36 * sizeof(short),    // 3 per triangle, 12 triangles
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &_indexBuffer,
        NULL);

    // lock i_buffer and load the indices into it
    _indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    _indexBuffer->Unlock();
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


void Engine::Update()
{
    for_each(_currentScene->_gameObjectList.begin(), _currentScene->_gameObjectList.end(), [](GameObject* gameObject) { gameObject->UpdateComponents(); });
}


void Engine::RenderFrame()
{
    _d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    _d3ddev->BeginScene();



    // SET UP THE PIPELINE

    /*D3DXMATRIX matRotateY;    // a matrix to store the rotation information
    D3DXMATRIX matRotateX;
    D3DXMATRIX matRotateZ;

    D3DXMATRIX matMove;
    D3DXMATRIX matScale;

    static float triangleMovementType = 1.0f;
    static float counter = 0.0f;    // an ever-increasing float value

    counter += (0.02f * triangleMovementType);
    // build a matrix to rotate the model based on the increasing float value
    D3DXMatrixRotationY(&matRotateY, counter);
    D3DXMatrixRotationX(&matRotateX, 0.0f);
    D3DXMatrixRotationZ(&matRotateZ, 0.0f);

    D3DXMatrixTranslation(&matMove, counter, counter, 0);

    D3DXMATRIX mathResult = matRotateX * matRotateY * matRotateZ;

    // tell Direct3D about our matrix
    _d3ddev->SetTransform(D3DTS_WORLD, &mathResult);

    
    _d3ddev->SetTransform(D3DTS_VIEW, &matView);
    _d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    // select the vertex buffer to display
    _d3ddev->SetStreamSource(0, _vertexBuffer, 0, sizeof(CUSTOMVERTEX));
    _d3ddev->SetIndices(_indexBuffer);

    // copy the vertex buffer indexed by the index buffer
    //_d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

    //LPCWSTR name = L"D:/Users/alesoudier/C++ Projects/EngineProject/Engine/Engine/Ressources/Tree.x";
    //LPD3DXMESH customMesh;

    //D3DXLoadMeshFromX(name, 0, _d3ddev, NULL, NULL, NULL, 0, &customMesh);

    customMesh->DrawSubset(0);*/

    ID3DXFont* g_font = NULL;

    D3DXCreateFont(_d3ddev,     //D3D Device

        22,               //Font height

        0,                //Font width

        FW_NORMAL,        //Font Weight

        1,                //MipLevels

        false,            //Italic

        DEFAULT_CHARSET,  //CharSet

        OUT_DEFAULT_PRECIS, //OutputPrecision

        ANTIALIASED_QUALITY, //Quality

        DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily

        L"Arial",          //pFacename,

        &g_font);         //ppFont

    RECT rect;
    SetRect(&rect, 500, 500, 1000, 1000);
    D3DXCOLOR color;
    color = D3DXCOLOR(255.0f, 255.0f, 255.0f,1);
    g_font->DrawTextW(NULL, L"Test", -1, &rect, DT_NOCLIP | DT_LEFT, color);

    /*LPD3DXMESH torusMesh;


    D3DXCreateTorus(_d3ddev, 1.0f, 2.0f, 200, 150, &torusMesh, NULL);

    torusMesh->DrawSubset(0);

    _d3ddev->EndScene();

    _d3ddev->Present(NULL, NULL, NULL, NULL);*/

    for_each(_currentScene->_gameObjectList.begin(), _currentScene->_gameObjectList.end(),
        [](GameObject* gameObject) { gameObject->GetComponent<MeshComponent>()->Draw(); });

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
    return true;
}

void Engine::Refresh()
{
    if (UpdateTime()) {
        Update();
        RenderFrame();
    }
}

void Engine::CleanD3D(void)
{
    _vertexBuffer->Release();
    _indexBuffer->Release();
    _d3ddev->Release();
    _d3d->Release();
}

Scene* Engine::CreateScene() {
    return new Scene(this);
}
