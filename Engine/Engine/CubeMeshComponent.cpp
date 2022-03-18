#include "pch.h"
#include "framework.h"

CubeMeshComponent::CubeMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void CubeMeshComponent::InitComponent()
{
    /*
    // create a vertex buffer interface called v_buffer
    _d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &_vertexBuffer,
        NULL);

    BYTE* pVoid;
    _vertexBuffer->Lock(0, 0, (void**)&pVoid, D3DLOCK_DISCARD);
    memcpy(pVoid, _vertices, sizeof(_vertices));
    _vertexBuffer->Unlock();

    _d3ddev->CreateIndexBuffer(36 * sizeof(short),    // 3 per triangle, 12 triangles
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &_indexBuffer,
        NULL);

    // lock i_buffer and load the indices into it
    _indexBuffer->Lock(0, 0, (void**)&pVoid, D3DLOCK_DISCARD);
    memcpy(pVoid, _indices, sizeof(_indices));
    _indexBuffer->Unlock();
    */
    D3DXCreateBox(_d3ddev, 1.0f, 1.0f, 1.0f, &_cubeMesh, NULL);

}

void CubeMeshComponent::Draw()
{
    MeshComponent::Draw();

    _d3ddev->SetFVF(CUSTOMFVF);
    
    _cubeMesh->DrawSubset(0);

    //_d3ddev->SetStreamSource(0, _vertexBuffer, 0, sizeof(CUSTOMVERTEX));
    //_d3ddev->SetIndices(_indexBuffer);    
    //_d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}
