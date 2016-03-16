#pragma once
#include "BoundingVolume.h"
class Ray
{
public:
	Ray();
	~Ray();

	D3DXVECTOR3 origin = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 0);

	static Ray CalcRayFromScreenPoint(POINT mousePoint);
	bool IsPicked(const BoundingSphere* sphere);
};

