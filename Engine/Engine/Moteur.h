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

#include <list>
#include <string>
#include <iostream>

#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

#include "MeshComponent.h"
#include "CubeMeshComponent.h"

#include "Scene.h"
#include "STimer.h"

#include "Camera.h"
#include "TextComponent.h"
#include "MouseManager.h"

#include "Engine.h"
