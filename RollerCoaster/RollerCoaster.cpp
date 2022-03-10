// RollerCoaster.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "RollerCoaster.h"

#define MAX_LOADSTRING 100
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

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
    DWORD color;
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

    d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
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
    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 10, 0, 6);

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
    
}

void cleanD3D(void)
{
    v_buffer->Release();
    d3ddev->Release();
    d3d->Release();
}

void init_graphics(void) 
{
    VOID* pVoid;

    //CUBE VERTEX BUFFER

    /*d3ddev->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &v_buffer, NULL);

    CUSTOMVERTEX vertices[] = {
    { -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },    // vertex 0
    { 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 0), },     // vertex 1
    { -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },   // 2
    { 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },  // 3
    { -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },     // ...
    { 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 0, 0), },
    { -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
    { 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 255), },
    };*/
    


    // PYRAMIDE VERTEX BUFFER

    /*struct CUSTOMVERTEX vertices[] =
    {
        // base
        { -3.0f, 0.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 3.0f, 0.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { -3.0f, 0.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { 3.0f, 0.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },

        // top
        { 0.0f, 7.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
    };

    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(5 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);
    */

    //HYPERCRAFT VERTEX BUFFER

    struct CUSTOMVERTEX vertices[] =
    {
        // fuselage
        { 3.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 0.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 0.0f, 0.0f, 10.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { -3.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 255), },

        // left gun
        { 3.2f, -1.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 3.2f, -1.0f, 11.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 2.0f, 1.0f, 2.0f, D3DCOLOR_XRGB(255, 0, 0), },

        // right gun
        { -3.2f, -1.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { -3.2f, -1.0f, 11.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { -2.0f, 1.0f, 2.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    d3ddev->CreateVertexBuffer(10 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);


    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

    //CUBE INDEX BUFFER
    /*
    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 0, 6,    // side 2
        6, 0, 2,
        7, 5, 6,    // side 3
        6, 5, 4,
        3, 1, 7,    // side 4
        7, 1, 5,
        4, 5, 0,    // side 5
        0, 5, 1,
        3, 7, 2,    // side 6
        2, 7, 6,
    };

    d3ddev->CreateIndexBuffer(36 * sizeof(short),    // 3 per triangle, 12 triangles
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &i_buffer,
        NULL);
    */
    
    //PYRAMIDE INDEX BUFFER

    // create the indices using an int array
    /*short indices[] =
    {
        0, 2, 1,    // base
        1, 2, 3,
        0, 1, 4,    // sides
        1, 3, 4,
        3, 2, 4,
        2, 0, 4,
    };

    // create a index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(18 * sizeof(short),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &i_buffer,
        NULL);
    */

    //HYPERCRAFT INDEX BUFFER

    short indices[] =
    {
        0, 1, 2,    // fuselage
        2, 1, 3,
        3, 1, 0,
        0, 2, 3,
        4, 5, 6,    // wings
        7, 8, 9,
    };

    // create a index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(18 * sizeof(short),
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
