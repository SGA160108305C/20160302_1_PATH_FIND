#include "stdafx.h"
#include "GameStateManager.h"


GameStateManager::GameStateManager()
{
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::Initialize()
{
	gameStates[GameStateType::STATE_DIRECT_X_BASE] = new GameState_DX_Base;
	gameStates[GameStateType::STATE_FVF] = new GameState_FVF;
	gameStates[GameStateType::STATE_TEXTURE] = new GameState_Texture;
	gameStates[GameStateType::STATE_HIERARCHY_ANIMATION] = new GameState_HierarchyAnimation;
	gameStates[GameStateType::STATE_LIGHT] = new GameState_Light;
	gameStates[GameStateType::STATE_OBJ_LOAD] = new GameState_OBJ_Load;
	gameStates[GameStateType::STATE_PICK_BASE] = new GameState_Picking;
	gameStates[GameStateType::STATE_VERTEX_BUFFER] = new GameState_VertexBuffer;	
	gameStates[GameStateType::STAET_ASE_LOAD] = new GameState_ASE_Load;
	gameStates[GameStateType::STATE_ACTIONS] = new GameState_Actions;
	gameStates[GameStateType::STATE_COLLISION] = new GameState_Collision;
	gameStates[GameStateType::STATE_PICK_MOUSE] = new GameState_PickMouse;
	gameStates[GameStateType::STATE_UI] = new GameState_UI;
	gameStates[GameStateType::STATE_PATH_FIND] = new GameState_PathFind;
	gameStates[GameStateType::STATE_HEIGHTMAP] = nullptr;
	gameStates[GameStateType::STATE_SKINNING] = nullptr;
	gameStates[GameStateType::STATE_FRUSTUM_CULLING] = nullptr;
	gameStates[GameStateType::STATE_BLENDING] = nullptr;
	gameStates[GameStateType::STATE_PARTICLE] = nullptr;
	gameStates[GameStateType::STATE_SHADER] = nullptr;
	gameStates[GameStateType::STATE_THREAD] = nullptr;
	
	currentState = GameStateType::STATE_PATH_FIND;
	gameStates[currentState]->OnEnterState();
}

void GameStateManager::Destroy()
{
	if (gameStates[currentState])
	{
		gameStates[currentState]->OnLeaveState();
	}
	for ( int i = 0; i < GameStateType::NUM_OF_STATE; ++i )
	{
		if ( gameStates[i] != nullptr )
		{
			SAFE_DELETE(gameStates[i]);
		}
	}
}

void GameStateManager::Update()
{
	gameStates[currentState]->Update();
}

void GameStateManager::Render()
{
	gameStates[currentState]->Render();
}

LRESULT GameStateManager::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return gameStates[currentState]->InputProc(hWnd, message, wParam, lParam);
	return 0;
}

bool GameStateManager::ChangeGameState(GameStateType state)
{
	bool result = false;
	if ( gameStates[state] )
	{
		gameStates[currentState]->OnLeaveState();
		currentState = state;
		gameStates[currentState]->OnEnterState();

		result = true;
	}

	return result;
}
