#include "pch.h"
#include "framework.h"

Mesh::~Mesh()
{
	if (pD3DXMtrlBuffer != NULL)
	{
		pD3DXMtrlBuffer = NULL;

	}
	
	(*g_pMeshTextures)->Release();
	g_pMeshTextures = NULL;

	_mesh->Release();
	_mesh = NULL;
}
