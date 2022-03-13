#pragma once
#include <windows.h>


#define MAX_LOADSTRING 100

class Engine;
class App
{

private:

	Engine* _engine = nullptr;

	HINSTANCE _hInstance;

	WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
	WCHAR szWindowClass[MAX_LOADSTRING];    // nom de la classe de fenêtre principale

	HWND _window;

	HACCEL _hAccelTable;

	MSG _msg;

	int SCREEN_WIDTH = 1920;
	int SCREEN_HEIGHT = 1080;

	bool _running = false;

	bool InitInstance(HINSTANCE hInstance, int nCmdShow);
	void HandleInputs();
	bool UpdateTime();


public:
	bool Init(HINSTANCE hInstance, int nCmdShow, HACCEL hAccelTable);
	void Loop();
	void Uninit();
};

