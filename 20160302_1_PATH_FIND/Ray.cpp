#include "stdafx.h"
#include "Ray.h"


Ray::Ray()
{
}


Ray::~Ray()
{
}

Ray Ray::CalcRayFromScreenPoint(POINT mousePoint)
{
	D3DVIEWPORT9 viewPort;
	GameManager::GetDevice()->GetViewport(&viewPort);
	D3DXMATRIXA16 projection;
	GameManager::GetDevice()->GetTransform(
		D3DTS_PROJECTION, &projection);

	Ray resultRay;
	//뷰포트와 프로젝션의 영향을 제거
	resultRay.direction.x = ((2.0f * mousePoint.x) / viewPort.Width - 1.0f) / projection(0, 0);
	resultRay.direction.y = ((-2.0f * mousePoint.y) / viewPort.Height + 1.0f) / projection(1, 1);
	resultRay.direction.z = 1.0f;

	//projection(0, 0);
	//projection._11;

	D3DXMATRIXA16 view, inverseView;
	GameManager::GetDevice()->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&inverseView, nullptr, &view);

	D3DXVec3TransformCoord(&resultRay.origin, &resultRay.origin, &inverseView);
	D3DXVec3TransformNormal(&resultRay.direction, &resultRay.direction, &inverseView);
	D3DXVec3Normalize(&resultRay.direction, &resultRay.direction);

	return resultRay;
}

bool Ray::IsPicked(const BoundingSphere* sphere)
{
	if (sphere)
	{
		D3DXVECTOR3 lengthVector = sphere->center - origin;
		float lengthSquare = D3DXVec3LengthSq(&lengthVector);
		float radiusSquare = sphere->radius * sphere->radius;
		if (lengthSquare < radiusSquare)
		{
			return true;	//광선이 구 안에서 시작된다.
		}

		float s = D3DXVec3Dot(&lengthVector, &direction);
		if (s < 0)
		{
			//광선의 시작점은 구의 밖에 있다.
			//두 백터의 내각이 90도가 넘어섰다.
			// == 둘이 만날일은 존재하지 않는다.
			return false;
		}

		float mSquare = lengthSquare - s * s;	//피타고라스의 정리를 이용해 m을 구한다.
		if (mSquare > radiusSquare)
		{
			//m이 구의 반지름보다 크면 이것도 만날일이 존재하지 않는다.
			return false;
		}
		else
		{
			//m이 구의 반지름보다 작다면 무조건 만난다.
			return true;
		}
	}

	return false;
}