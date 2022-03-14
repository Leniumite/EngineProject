#pragma once



#pragma comment(lib,"d3d9.lib")
#pragma comment( lib, "winmm.lib")
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
#include "STimer.h"