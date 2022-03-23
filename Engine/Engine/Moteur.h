#pragma once



#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9d.lib")
#pragma comment(lib,"d3dx9.lib")
#endif

#include <windows.h>
#include <windowsx.h>
#include <assert.h>
#include <comdef.h>

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
#include <vector>

#include "Component.h"
#include "Transform.h"
#include "LightComponent.h"


#include "GameObject.h"

#include "MeshComponent.h"
#include "CubeMeshComponent.h"
#include "PolygonMeshComponent.h"
#include "SphereMeshComponent.h"
#include "TorusMeshComponent.h"
#include "TeapotMeshComponent.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

#include "Scene.h"
#include "STimer.h"

#include "CameraComponent.h"
#include "TextComponent.h"
#include "MouseManager.h"


#include "Engine.h"
