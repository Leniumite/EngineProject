#include "pch.h"
#include "CubeMeshComponent.h"

void CubeMeshComponent::InitMesh()
{
    MeshComponent::InitMesh();

    VOID* pVoid;

    // create a vertex buffer interface called v_buffer
    _d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        _vertexBuffer,
        NULL);

    (*_vertexBuffer)->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, _vertices, sizeof(_vertices));
    (*_vertexBuffer)->Unlock();

    _d3ddev->CreateIndexBuffer(36 * sizeof(short),    // 3 per triangle, 12 triangles
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        _indexBuffer,
        NULL);

    // lock i_buffer and load the indices into it
    (*_indexBuffer)->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, _indices, sizeof(_indices));
    (*_indexBuffer)->Unlock();


    _d3ddev->SetStreamSource(m_id, *_vertexBuffer, m_id, sizeof(CUSTOMVERTEX));
    _d3ddev->SetIndices(*_indexBuffer);
}

void CubeMeshComponent::Draw()
{

    _d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}
