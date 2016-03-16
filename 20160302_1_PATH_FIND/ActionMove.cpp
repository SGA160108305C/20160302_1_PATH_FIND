#include "stdafx.h"
#include "ActionMove.h"


ActionMove::ActionMove()
{
}


ActionMove::~ActionMove()
{
}

void ActionMove::Start()
{
	if (!target)
		return;

	isStart = true;
	passedTime = 0.0f;
	target->SetPosition(start);

	D3DXVECTOR3 a(0, 0, 1);
	D3DXVECTOR3 b = goal - start;

	float aLength = D3DXVec3Length(&a);
	float bLength = D3DXVec3Length(&b);
	float dot = D3DXVec3Dot(&a, &b);	

	float angle = acos(dot / (aLength * bLength));

	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &a, &b);
	if (cross.y < 0)
	{
		//반시계 방향이다.
		angle *= -1;
	}

	//D3DXVECTOR3 c(1, 0, 0);	//180.0도 구할때 쓰는 방식
	//if (D3DXVec3Dot(&b, &c) < 0.0f)
	//{
	//	angle += D3DX_PI;
	//}
	target->SetAngle(angle);
}

void ActionMove::Update()
{
	if (!target || isStart == false)
		return;

	passedTime += (float)GameManager::GetTick();
	if (passedTime > durationTime)
	{
		target->SetPosition(goal);
		isStart = false;
		if (actionDelegate)
		{
			actionDelegate->OnActionFinish(this);
		}
		return;
	}

	D3DXVECTOR3 pos;
	D3DXVec3Lerp(&pos, &start, &goal, passedTime / durationTime);
	target->SetPosition(pos);
}

void ActionMove::Destroy()
{
}
