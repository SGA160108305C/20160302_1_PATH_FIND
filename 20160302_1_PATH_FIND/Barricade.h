#pragma once
#include "GameObject.h"

class Barricade :
	public GameObject
{
public:
	Barricade();
	virtual ~Barricade();

	void Initialize(D3DXVECTOR3& pos, float radius = 1.0f);
	virtual void Destroy() override;
	virtual void Render() override;

	inline BoundingSphere* GetBoundingSphere(){ return &boundingSphere; }
	inline float GetRadius(){ return boundingSphere.radius; }

protected:
	BoundingSphere boundingSphere = BoundingSphere(D3DXVECTOR3(0, 0, 0), 1.0f);
	LPD3DXMESH barricadeMesh = nullptr;
	LPD3DXMESH boundingSphereMesh = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX boundingWorld;
	D3DXVECTOR3 localPivot = D3DXVECTOR3(0, 0, 0);
	D3DMATERIAL9 baseMaterial;

	bool showBoundingSphere = true;
};

