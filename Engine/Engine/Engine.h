#pragma once

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

	void InitD3D();
	void InitGraphics();
	void InitLights();
	void Update();
	void RenderFrame();

	bool UpdateTime();

public:

	MouseManager _MM;

	Engine() {}
	virtual ~Engine() {}

	void Init(HWND window, int screenWidth, int screenHeight);

	void LoadScene(Scene* newScene) { _currentScene = newScene; };

	void Refresh();

	void CleanD3D();

	Scene* CreateScene();

	inline LPDIRECT3DDEVICE9 GetDevice() { return _d3ddev; };

	void DrawTextString(int x, int y, DWORD color, const char* str);

};
