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
#include <dwmapi.h>
#include <debugapi.h>

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
#include <random>


#include "Component.h"
#include "Transform.h"
#include "LightComponent.h"


#include "GameObject.h"
#include "Particle.h"


#include "Listener.h"
#include "MeshComponent.h"
#include "CubeMeshComponent.h"
#include "PolygonMeshComponent.h"
#include "SphereMeshComponent.h"
#include "TorusMeshComponent.h"
#include "TeapotMeshComponent.h"
#include "ParticleSystemComponent.h"


#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

#include "CollisionManager.h"

#include "Scene.h"
#include "STimer.h"

#include "CameraComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"
#include "MouseManager.h"
#include "Rigidbody.h"

#include "Engine.h"
