#include "stdafx.h"
#include "PathNode.h"


PathNode::PathNode()
{
}


PathNode::~PathNode()
{
}

void PathNode::Initialize(D3DXVECTOR3& pos, float radius /*= 0.5f*/)
{
	position = pos;
	localPivot = D3DXVECTOR3(0, 0, 0);	 

	D3DXCreateSphere(GameManager::GetDevice(), radius, 16, 8, &nodeMesh, nullptr); 

	D3DXMatrixIdentity(&world);

	D3DXMATRIX local;
	D3DXMatrixTranslation(&local, localPivot.x, localPivot.y, localPivot.z);
	world *= local;

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);
	world *= translation; 

	ZeroMemory(&baseMaterial, sizeof(D3DMATERIAL9));
	baseMaterial.Ambient = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);
	baseMaterial.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); 
}

void PathNode::Destroy()
{
	SAFE_RELEASE(nodeMesh);
}

void PathNode::Render()
{
	if (nodeMesh)
	{
		GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
		GameManager::GetDevice()->SetMaterial(&baseMaterial);
		GameManager::GetDevice()->SetTexture(0, nullptr);
		GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
		nodeMesh->DrawSubset(0);
	}
}