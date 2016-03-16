#include "stdafx.h"
#include "GameState_Collision.h"
#include "ActionMove.h"
#include "Collision.h"


GameState_Collision::GameState_Collision()
{
}


GameState_Collision::~GameState_Collision()
{
}

void GameState_Collision::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}	
	if ( girl == nullptr )
	{
		girl = new Character_Collision;
		girl->Initialize();			
	}
	if (sphere == nullptr)
	{
		sphere = new Collider_Sphere;
		sphere->Initialize(D3DXVECTOR3(10, 0, 0), 3.0f);		
		sphere->SetMaterialColor(D3DXCOLOR(0, 1, 0, 1));			
	}
	if (box == nullptr)
	{
		box = new Collider_Box;
		box->Initialize(D3DXVECTOR3(-10, 0, 0), D3DXVECTOR3(-9, 1, 1));
		box->SetMaterialColor(D3DXCOLOR(0, 0, 1, 1));
	}

	Reset();
}

void GameState_Collision::Destroy()
{	
	SAFE_DELETE(box);
	SAFE_DELETE(sphere);
	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_Collision::Reset()
{
}

void GameState_Collision::Update()
{
	if ( girl )
	{
		girl->Update();
	}
	if (sphere)
	{
		sphere->Update();
	}
	if (box)
	{
		box->Update();
	}

	//if (Collision::IsSphereToSphere(girl->GetBouningSphere(), sphere->GetBoundingSphere()))
	//{
	//	sphere->SetMaterialColor(D3DXCOLOR(1,0,0,1));
	//}
	//else
	//{
	//	sphere->SetMaterialColor(D3DXCOLOR(0, 1, 0, 1));
	//}
}

void GameState_Collision::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( girl )
	{
		girl->Render();
	}
	if (sphere)
	{
		sphere->Render();
	}
	if (box)
	{
		box->Render();
	}
}

void GameState_Collision::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_Collision::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_Collision::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
