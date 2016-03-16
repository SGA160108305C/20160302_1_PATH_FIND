#include "stdafx.h"
#include "Character_PathMove.h"
#include "ActionMove.h"

Character_PathMove::Character_PathMove()
{
}


Character_PathMove::~Character_PathMove()
{
}

LRESULT Character_PathMove::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch ( message )
	{
		case WM_RBUTTONDOWN:
			{
				//POINT mousePoint;
				//mousePoint.x = GET_X_LPARAM(lParam);
				//mousePoint.y = GET_Y_LPARAM(lParam);				
				//result = WM_RBUTTONDOWN;
			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT mousePoint;
				mousePoint.x = GET_X_LPARAM(lParam);
				mousePoint.y = GET_Y_LPARAM(lParam);				

				if ( grid && pathFinder )
				{
					Ray ray = Ray::CalcRayFromScreenPoint(mousePoint);

					const std::vector<D3DXVECTOR3>& groundVertex = grid->GetGroundVertex();

					for ( unsigned int i = 0; i < groundVertex.size(); i += 3 )
					{
						float u, v, distance;
						if ( D3DXIntersectTri(&groundVertex[i], &groundVertex[i + 1], &groundVertex[i + 2],
							&ray.origin, &ray.direction, &u, &v, &distance) )
						{
							D3DXVECTOR3 targetPosition = ray.origin + ray.direction * distance;

							bool isCollision = pathFinder->CheckBarricadeCollision(position, targetPosition);
							if ( isCollision == true )
							{
								//길찾기 시작
								int startIndex = pathFinder->FindNearestPathNode(position);
								int goalIndex = pathFinder->FindNearestPathNode(targetPosition);
								if ( startIndex != -1 && goalIndex != -1 )
								{
									std::list<int> path;
									pathFinder->PathFind(path, startIndex, goalIndex);
									pathFinder->PathOptimize(path, position, targetPosition);

									//액션 추가
									SAFE_DELETE(action);

									ActionSequence* sequence = new ActionSequence;
									auto iterStart = path.cbegin();
									auto iterNext = ++path.cbegin();
									float length = 1.0f;
									D3DXVECTOR3 temp;
									
									//출발점 -> 첫번째 노드
									ActionMove* firstMove = new ActionMove;
									const D3DXVECTOR3& startPos = pathFinder->GetPathNodePosition(*iterStart);
									temp = startPos - position;
									length = D3DXVec3Length(&temp);									
									firstMove->SetStart(position);
									firstMove->SetGoal(startPos);
									firstMove->SetDurationTime(0.1f * length);
									firstMove->SetTarget(this);
									firstMove->SetDelegate(sequence);
									sequence->AddAction(firstMove);

									//첫번째 노드 -> 마지막 노드
									while ( iterStart != path.cend() && iterNext != path.cend() )
									{
										ActionMove* move = new ActionMove;
										
										const D3DXVECTOR3& start = pathFinder->GetPathNodePosition(*iterStart);
										const D3DXVECTOR3& next = pathFinder->GetPathNodePosition(*iterNext);
										temp = next - start;
										length = D3DXVec3Length(&temp);
										move->SetStart(start);
										move->SetGoal(next);
										move->SetDurationTime(0.1f * length);
										move->SetTarget(this);
										move->SetDelegate(sequence);
										sequence->AddAction(move);

										++iterStart;
										++iterNext;
									}

									//마지막 노드 -> 도착점
									ActionMove* LastMove = new ActionMove;
									const D3DXVECTOR3& lastPos = pathFinder->GetPathNodePosition(*iterStart);
									temp = targetPosition - lastPos;
									length = D3DXVec3Length(&temp);
									LastMove->SetStart(lastPos);
									LastMove->SetGoal(targetPosition);
									LastMove->SetDurationTime(0.1f * length);
									LastMove->SetTarget(this);
									LastMove->SetDelegate(sequence);
									sequence->AddAction(LastMove);

									//세팅 및 시작
									action = sequence;
									action->Start();
								}
							}
							else
							{
								//그냥 이동
								D3DXVECTOR3 targetLength = targetPosition - position;
								float length = D3DXVec3Length(&targetLength);
								//OutputDebugStringA(std::string("lenght : " + std::to_string(length) + "\n").c_str());

								SAFE_DELETE(action);
								ActionMove* move = new ActionMove;
								move->SetStart(position);
								move->SetGoal(targetPosition);
								move->SetDurationTime(0.1f * length);
								move->SetTarget(this);
								move->Start();

								SetAction(move);
							}						
						}
					}
				}

				result = WM_LBUTTONDOWN;
			}
			break;
	}
	return result;
}