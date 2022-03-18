#pragma once



#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <windows.h>
#include <windowsx.h>
#include <assert.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <time.h>
#include <timeapi.h>
#include <ctime>
#include <algorithm>

#include "list"
#include "Component.h"
#include "Transform.h"

#include "GameObject.h"
#include "MeshComponent.h"
#include "CubeMeshComponent.h"
#include "Scene.h"
#include "STimer.h"
#include "Component.h"
#include "Camera.h"
#include "TextComponent.h"
#include "MouseManager.h"

#define MAX_LOADSTRING 100

class Engine
{
private:

	HWND _currentWindow;
	int _screenWidth;
	int _screenHeight;

	bool _running;

	Scene* _currentScene;

	STimer* _timer;

	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9 _indexBuffer = NULL;

	void InitD3D();
	void InitGraphics();
	void InitLights();
	void Update();
	void RenderFrame();

	bool UpdateTime();

public:

	Camera _cam;
	MouseManager _MM;


	void Init(HWND window, int screenWidth, int screenHeight);

	void LoadScene(Scene* newScene) { _currentScene = newScene; };

	void Refresh();

	void CleanD3D();

	Scene* CreateScene();

	inline LPDIRECT3DDEVICE9 GetDevice() { return _d3ddev; };

	void DrawTextString(int x, int y, DWORD color, const char* str);

};
