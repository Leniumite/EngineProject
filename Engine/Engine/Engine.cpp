// Engine.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"


#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)


struct CUSTOMVERTEX
{
    float x, y, z;
    D3DVECTOR NORMAL;
};


void Engine::Init(HWND window, int screenWidth, int screenHeight)
{
	_currentWindow = window;
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;
    InitD3D();
}


Scene* Engine::CreateNewScene()
{
    Scene* newScene = new Scene();
    _sceneList.push_back(newScene);
    return newScene;
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

    InitGraphics();
    InitLights();

    _d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
    _d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    _d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    _d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
}

void Engine::InitGraphics() {

}

void Engine::InitLights() {

}


void Engine::Update()
{

}


void Engine::RenderFrame()
{
    _d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    _d3ddev->BeginScene();

    // select which vertex format we are using
    _d3ddev->SetFVF(CUSTOMFVF);

    // SET UP THE PIPELINE

    D3DXMATRIX matRotateY;    // a matrix to store the rotation information
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

    D3DXMATRIX matView;    // the view transform matrix

    //Transform test;

    D3DXVECTOR3 camPos, camLookAt, camUp;
    camPos = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
    camLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    D3DXMatrixLookAtLH(&matView,
        &camPos,    // the camera position
        &camLookAt,    // the look-at position
        &camUp);    // the up direction

    _d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        (FLOAT)_screenWidth / (FLOAT)_screenHeight, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane

    _d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    // select the vertex buffer to display
    _d3ddev->SetStreamSource(0, _vertexBuffer, 0, sizeof(CUSTOMVERTEX));
    _d3ddev->SetIndices(_indexBuffer);

    // copy the vertex buffer indexed by the index buffer
    _d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

    _d3ddev->EndScene();

    _d3ddev->Present(NULL, NULL, NULL, NULL);

}

void Engine::CleanD3D(void)
{
    _vertexBuffer->Release();
    _indexBuffer->Release();
    _d3ddev->Release();
    _d3d->Release();
}
