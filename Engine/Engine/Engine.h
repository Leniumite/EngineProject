#pragma once



#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")


#ifdef _DEBUG 
#pragma comment(lib,"d3dx9d.lib")
#else 
#pragma comment(lib,"d3dx9.lib")
#endif

#include <windows.h>
#include <assert.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#include <time.h>
#include <timeapi.h>
#include <ctime>
#include <algorithm>

#include "Transform.h"
#include "list"
#include "Scene.h"
#include "STimer.h"
#include "Component.h"


#define MAX_LOADSTRING 100



class Engine
{
private:

	HWND _currentWindow;
	int _screenWidth;
	int _screenHeight;

	bool _running;	

	Scene _currentScene;

	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9 _indexBuffer = NULL;

	void InitD3D();
	void InitGraphics();
	void InitLights();
	

public:

	void Init(HWND window, int screenWidth, int screenHeight);

	void LoadScene(Scene newScene) { _currentScene = newScene; };

	void Update();
	void RenderFrame();
	void CleanD3D();

};