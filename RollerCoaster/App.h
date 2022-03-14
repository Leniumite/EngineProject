#pragma once
#include "framework.h"

#define MAX_LOADSTRING 100

class App
{

private:

	Engine _engine;

	HINSTANCE _hInstance;

	WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre

	HWND _window;

	HACCEL _hAccelTable;

	MSG _msg;

	STimer _sTimer;

	int SCREEN_WIDTH = 1920;
	int SCREEN_HEIGHT = 1080;

	bool _running = false;

	bool InitInstance(HINSTANCE hInstance, int nCmdShow);
	void HandleInputs();
	bool UpdateTime();


public:

	App();
	bool Init(HINSTANCE hInstance, int nCmdShow, HACCEL hAccelTable);
	void Loop();
	void Uninit();

	MSG GetMessage() { return _msg; }
};

