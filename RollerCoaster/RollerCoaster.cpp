// RollerCoaster.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "RollerCoaster.h"

#define MAX_LOADSTRING 100
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
HWND hWnd;
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;

float index = 0;

HRESULT CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL pool, LPDIRECT3DVERTEXBUFFER9 ppVertexBuffer, HANDLE* pShareHandle);


struct CUSTOMVERTEX
{
    float x, y, z;
    D3DVECTOR NORMAL;
};



// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    // Initialise les chaînes globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROLLERCOASTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROLLERCOASTER));
    initD3D(hWnd);
    MSG msg;
    bool running = true;
    while (running)
    {
        render_frame();

        // Boucle de messages principale :
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
        }
    }

    cleanD3D();
    return (int) msg.wParam;
}



//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROLLERCOASTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROLLERCOASTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
     CW_USEDEFAULT, 0, SCREEN_WIDTH,  SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Ajoutez ici le code de dessin qui utilise hdc...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &d3ddev);

    init_graphics();
    init_light();

    d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
    d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
}

void render_frame()
{
    
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    //d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);

    // SET UP THE PIPELINE

    D3DXMATRIX matRotateY;    // a matrix to store the rotation information
    D3DXMATRIX matRotateX;
    D3DXMATRIX matRotateZ;

    D3DXMATRIX matMove;

    static float triangleMovementType = 1.0f;
    static float counter = 0.0f;    // an ever-increasing float value

    /*if (counter <= -4.0f) {
        triangleMovementType = 1;
    }
    else if (counter > 4.0f) {
        triangleMovementType = -1;
    }*/

    counter += (0.02f * triangleMovementType);
    // build a matrix to rotate the model based on the increasing float value
    D3DXMatrixRotationY(&matRotateY, counter);
    D3DXMatrixRotationX(&matRotateX, 0.0f);
    D3DXMatrixRotationZ(&matRotateZ, 0.0f);
    
    D3DXMatrixTranslation(&matMove, counter,counter,0);

    D3DXMATRIX mathResult =  matRotateX * matRotateY * matRotateZ;

    // tell Direct3D about our matrix
    d3ddev->SetTransform(D3DTS_WORLD, &mathResult);

    D3DXMATRIX matView;    // the view transform matrix


    D3DXVECTOR3 camPos, camLookAt, camUp;
    camPos = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
    camLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    D3DXMatrixLookAtLH(&matView,
        &camPos,    // the camera position
        &camLookAt,    // the look-at position
        &camUp);    // the up direction

    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane

    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    // select the vertex buffer to display
    d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
    d3ddev->SetIndices(i_buffer);

    // copy the vertex buffer indexed by the index buffer
    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
    
}

void cleanD3D(void)
{
    v_buffer->Release();
    i_buffer->Release();
    d3ddev->Release();
    d3d->Release();
}

// this is the function that sets up the lights and materials
void init_light(void)
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

    d3ddev->SetLight(0, &blueLight);    // send the light struct properties to light #0
    d3ddev->LightEnable(0, TRUE);    // turn on light #0

    ZeroMemory(&redLight, sizeof(redLight));    // clear out the light struct for use
    redLight.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    redLight.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);    // set the light's color
    redLight.Direction.x = 1.0f; //Ouais c'est pas beau, mais pas de conversion possible entre un D3DVECTOR et D3DXVECTOR3
    redLight.Direction.y = 0.0f;
    redLight.Direction.z = 0.0f;

    d3ddev->SetLight(1, &redLight);    // send the light struct properties to light #0
    d3ddev->LightEnable(1, TRUE);    // turn on light #0

    ZeroMemory(&whiteLight, sizeof(whiteLight));    // clear out the light struct for use
    whiteLight.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    whiteLight.Diffuse = D3DXCOLOR(.8f, .8f, .8f, 1.0f);    // set the light's color
    whiteLight.Direction.x = 0.0f; //Ouais c'est pas beau, mais pas de conversion possible entre un D3DVECTOR et D3DXVECTOR3
    whiteLight.Direction.y = 0.0f;
    whiteLight.Direction.z = -1.0f;

    d3ddev->SetLight(2, &whiteLight);    // send the light struct properties to light #0
    d3ddev->LightEnable(2, TRUE);    // turn on light #0

    ZeroMemory(&material, sizeof(D3DMATERIAL9));
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}


void init_graphics(void) 
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
    d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);


    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

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

    d3ddev->CreateIndexBuffer(36 * sizeof(short),    // 3 per triangle, 12 triangles
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &i_buffer,
        NULL);

    // lock i_buffer and load the indices into it
    i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    i_buffer->Unlock();

    
}
