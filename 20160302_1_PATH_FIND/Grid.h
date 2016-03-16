#pragma once
#include "FVF.h"

class Grid
{
public:
	Grid();
	~Grid();

	void Initialize(int lineCount = 30, float interval = 1.0f);
	void Destroy();
	void Render();

	const std::vector<D3DXVECTOR3>& GetGroundVertex(){ return groundVertex; }

private:
	std::vector<FVF_PositionColor>	vertices;
	std::vector<D3DXVECTOR3> groundVertex;

	static const int axisCount = 3;

	D3DXMATRIXA16 world;
	D3DMATERIAL9 groundMaterial;
};

