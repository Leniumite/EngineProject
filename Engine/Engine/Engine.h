#pragma once



#pragma comment(lib,"d3d9.lib")

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

#include "Transform.h"
#include "list"
#include "Scene.h"
#include "STimer.h"

#define MAX_LOADSTRING 100



/*struct CUSTOMVERTEX
{
	float x, y, z;
	D3DVECTOR NORMAL;
};*/

class Engine
{
private:

	HWND _currentWindow;
	int _screenWidth;
	int _screenHeight;

	bool _running;

	list<Scene*> _sceneList;
	

	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9 _indexBuffer = NULL;

	void InitD3D();
	void InitGraphics();
	void InitLights();
	

	

public:

	Engine(HWND window, int screenWidth, int screenHeight);

	void Update();
	void RenderFrame();
	void CleanD3D();
	Scene* CreateNewScene();

};