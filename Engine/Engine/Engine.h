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