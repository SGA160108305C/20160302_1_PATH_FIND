#include "stdafx.h"
#include "Character_MouseMove.h"


Character_MouseMove::Character_MouseMove()
{
}


Character_MouseMove::~Character_MouseMove()
{
}

LRESULT Character_MouseMove::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
		case WM_LBUTTONDOWN:
			{
				POINT mousePoint;
				mousePoint.x = GET_X_LPARAM(lParam);
				mousePoint.y = GET_Y_LPARAM(lParam);
				Ray ray = Ray::CalcRayFromScreenPoint(mousePoint);
				char temp[256];
				sprintf_s(temp, 
					"direction : %.2f, %.2f, %.2f\n", 
					ray.direction.x, ray.direction.y, ray.direction.z);
				//OutputDebugStringA(temp);
				sprintf_s(temp, 
					"origin : %.2f, %.2f, %.2f\n", 
					ray.origin.x, ray.origin.y, ray.origin.z);
				//OutputDebugStringA(temp);

				if (grid)
				{
					const std::vector<D3DXVECTOR3>& groundVertex = 
						grid->GetGroundVertex();

					for (UINT32 i = 0; i < groundVertex.size(); i += 3)
					{
						float u, v, distance;
						if (D3DXIntersectTri(
							&groundVertex[i],
							&groundVertex[i + 1],
							&groundVertex[i + 2],
							&ray.origin,
							&ray.direction,
							&u, &v, &distance))
						{
							D3DXVECTOR3 target = ray.origin + ray.direction * distance;
							sprintf_s(temp,
								"target : %.2f, %.2f, %.2f\n",
								target.x, target.y, target.z);
							//OutputDebugStringA(temp);

							D3DXVECTOR3 targetLenght = target - position;
							float length = D3DXVec3Length(&targetLenght);

							SAFE_DELETE(action);
							ActionMove* move = new ActionMove;
							move->SetStart(position);
							move->SetGoal(target);
							move->SetTarget(this);
							move->SetDurationTime(0.1f*length);
							move->Start();
							SetAction(move);
						}
					}
					
				}
				result = WM_LBUTTONDOWN;
				
			}
			break;
		case WM_RBUTTONDOWN:
			{
				POINT mousePoint;
				mousePoint.x = GET_X_LPARAM(lParam);
				mousePoint.y = GET_Y_LPARAM(lParam);
				Ray ray = Ray::CalcRayFromScreenPoint(mousePoint);
				bool isPick = ray.IsPicked(&currentBoundingSphere);
				aseRootFrame->SetTextureOn(isPick);
				result = WM_RBUTTONDOWN;
			}
			break;
	}
	return result;
}