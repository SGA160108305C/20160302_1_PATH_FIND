#pragma once
#include "GameObject.h"
#include "Dijkstra.h"
class PathNode :
	public GameObject, public DijkstraNode
{
public:
	PathNode();
	virtual ~PathNode();

	void Initialize(D3DXVECTOR3& pos, float radius = 0.5f);
	virtual void Destroy() override;
	virtual void Render() override;

protected:
	LPD3DXMESH nodeMesh = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX boundingWorld;
	D3DXVECTOR3 localPivot = D3DXVECTOR3(0, 0, 0);

	D3DMATERIAL9 baseMaterial;
};

