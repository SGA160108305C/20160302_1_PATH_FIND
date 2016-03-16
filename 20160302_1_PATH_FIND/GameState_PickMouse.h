#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Collider_Sphere.h"
#include "Collider_Box.h"
#include "Character_MouseMove.h"

class GameState_PickMouse :
	public GameState
{
public:
	GameState_PickMouse();
	virtual ~GameState_PickMouse();

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
	Character_MouseMove* girl = nullptr;
	

};

