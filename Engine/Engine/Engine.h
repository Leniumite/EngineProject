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

	void Update();
	void RenderFrame();

	bool UpdateTime();
	void DestroyGameobjectWaiting();
	list<GameObject*> objectToDestroy = list<GameObject*>();

public:
	MouseManager _MM;
	CollisionManager _CM;

	D3DXMATRIX _identityMatrix;
	D3DMATERIAL9 _defaultMaterial;

	Engine() {}
	virtual ~Engine() {}

	void Init(HWND window, int screenWidth, int screenHeight);

	inline Scene* GetScene() { return _currentScene; }

	void LoadScene(Scene* newScene);

	inline HWND GetWindow() { return _currentWindow; }

	void Refresh();

	void Uninit();

	Scene* CreateScene();

	STimer* GetTimer() { return _timer; }

	inline LPDIRECT3DDEVICE9 GetDevice() { return _d3ddev; }

	void DrawTextString(int x, int y, DWORD color, const char* str);

	void Destroy(GameObject* go, float timer = 0.0f);

};
