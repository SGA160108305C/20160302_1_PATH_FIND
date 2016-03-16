#include "stdafx.h"
#include "GameState_PathFind.h"


GameState_PathFind::GameState_PathFind()
{
}


GameState_PathFind::~GameState_PathFind()
{
}

void GameState_PathFind::Initialize()
{
	if (grid == nullptr)
	{
		grid = new Grid;
		grid->Initialize();
	}
	if (pathFinder == nullptr)	
	{
		pathFinder = new PathFinder;
		pathFinder->Initialize();
	}
	if ( girl == nullptr )
	{
		girl = new Character_PathMove();
		girl->Initialize();
		girl->SetGrid(grid);
		girl->SetPathFinder(pathFinder);
	}
}

void GameState_PathFind::Destroy()
{
	SAFE_DELETE(girl);
	SAFE_DELETE(pathFinder);
	SAFE_DELETE(grid);
}

void GameState_PathFind::Reset()
{
}

void GameState_PathFind::Update()
{
	if ( girl )
	{
		girl->Update();
	}
}

void GameState_PathFind::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( pathFinder )
	{
		pathFinder->Render();
	}
	if ( girl )
	{
		girl->Render();
	}


	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	Font::GetFont()->DrawTextA(NULL, "GameState_PathFind", strlen("GameState_PathFind"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_PathFind::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(40.0f);
	
	Initialize();
}

void GameState_PathFind::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_PathFind::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && girl )
	{
		girl->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
