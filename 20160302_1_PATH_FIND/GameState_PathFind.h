#pragma once
#include "GameState.h"
#include "Grid.h"
#include "PathFinder.h"
#include "Character_PathMove.h"

class GameState_PathFind :
	public GameState
{
public:
	GameState_PathFind();
	virtual ~GameState_PathFind();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Reset() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	Grid* grid = nullptr;
	PathFinder* pathFinder = nullptr;
	Character_PathMove* girl = nullptr;
};

