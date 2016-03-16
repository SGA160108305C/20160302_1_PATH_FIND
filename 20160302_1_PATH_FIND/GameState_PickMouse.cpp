#include "stdafx.h"
#include "GameState_PickMouse.h"
#include "ActionMove.h"
#include "Collision.h"


GameState_PickMouse::GameState_PickMouse()
{
}


GameState_PickMouse::~GameState_PickMouse()
{
}

void GameState_PickMouse::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}	
	if ( girl == nullptr )
	{
		girl = new Character_MouseMove;
		girl->Initialize();			
		girl->SetGrid(grid);
	}

	Reset();
}

void GameState_PickMouse::Destroy()
{	
	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_PickMouse::Reset()
{
}

void GameState_PickMouse::Update()
{
	if ( girl )
	{
		girl->Update();
	}
}

void GameState_PickMouse::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( girl )
	{
		girl->Render();
	}
}

void GameState_PickMouse::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_PickMouse::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_PickMouse::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (girl)
	{
		girl->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
