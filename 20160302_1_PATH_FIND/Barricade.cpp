#include "stdafx.h"
#include "Barricade.h"


Barricade::Barricade()
{
}


Barricade::~Barricade()
{
}

void Barricade::Initialize(D3DXVECTOR3& pos, float radius /*= 1.0f*/)
{
	position = pos;
	localPivot = D3DXVECTOR3(0, 0, 0);

	boundingSphere.radius = radius;
	boundingSphere.center = position + localPivot;
	

	D3DXCreateSphere(GameManager::GetDevice(), radius, 16, 8, &barricadeMesh, nullptr);
	D3DXCreateSphere(GameManager::GetDevice(), boundingSphere.radius, 16, 8, &boundingSphereMesh, nullptr);

	D3DXMatrixIdentity(&world);

	D3DXMATRIX local;
	D3DXMatrixTranslation(&local, localPivot.x, localPivot.y, localPivot.z);
	world *= local;

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);
	world *= translation;
	
	D3DXMatrixIdentity(&boundingWorld);
	D3DXMATRIX boundingRotation, boundingTranslation;
	D3DXMatrixRotationX(&boundingRotation, D3DX_PI * 0.5f);
	D3DXMatrixTranslation(&boundingTranslation, boundingSphere.center.x, boundingSphere.center.y, boundingSphere.center.z);
	boundingWorld *= ( boundingRotation * boundingTranslation );

	ZeroMemory(&baseMaterial, sizeof(D3DMATERIAL9));
	baseMaterial.Ambient = D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f);
	baseMaterial.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	showBoundingSphere = false;
}

void Barricade::Destroy()
{
	SAFE_RELEASE(boundingSphereMesh);
	SAFE_RELEASE(barricadeMesh);
}

void Barricade::Render()
{
	if (barricadeMesh)
	{
		GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
		GameManager::GetDevice()->SetMaterial(&baseMaterial);
		GameManager::GetDevice()->SetTexture(0, nullptr);
		GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
		barricadeMesh->DrawSubset(0);
	}
	if ( showBoundingSphere && boundingSphereMesh )
	{
		GameManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		GameManager::GetDevice()->SetTexture(0, nullptr);
		GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &boundingWorld);
		boundingSphereMesh->DrawSubset(0);
		GameManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}