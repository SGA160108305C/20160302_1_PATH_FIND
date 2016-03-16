#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Character_Collision.h"
#include "Collider_Sphere.h"
#include "Collider_Box.h"

class GameState_Collision :
	public GameState
{
public:
	GameState_Collision();
	virtual ~GameState_Collision();

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
	Character_Collision* girl = nullptr;
	
	Collider_Sphere* sphere = nullptr;
	Collider_Box* box = nullptr;

};

