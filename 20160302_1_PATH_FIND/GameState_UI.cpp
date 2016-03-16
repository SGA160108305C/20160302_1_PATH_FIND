#include "stdafx.h"
#include "GameState_UI.h"
#include "ActionMove.h"
#include "Collision.h"


GameState_UI::GameState_UI()
{
}


GameState_UI::~GameState_UI()
{
}

void GameState_UI::Initialize()
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
	
	UI_Image* uiImage = new  UI_Image;
	uiImage->SetTexture("./UI/panel-info.png");
	uiImage->SetPosition(0, 0, 0);
	UI_Manager::Get().SetRoot(uiImage);
	

	UI_Text* uiText = new UI_Text;
	uiText->SetFont(Font::GetFont());
	uiText->SetText("Hello World");
	uiText->SetPosition(10, 100, 0);
	uiText->SetSize(300, 70);
	uiText->SetTextColor(D3DCOLOR_XRGB(255,255,0));
	uiText->SetTextFormat(DT_CENTER);
	uiImage->AddChild(uiText);

	UI_Button* uiButton = new UI_Button;
	uiButton->SetTexture("./UI/btn-med-up.png", "./UI/btn-med-over.png", "./UI/btn-med-down.png");
	uiButton->SetPosition(135, 330, 0);
	/*uiButton->OnClick = std::bind(
		&UI_Functions::ClickTest,
		std::ref(UI_Manager::Get().func)
		);*/
	uiButton->OnClick = std::bind(
		&UI_Functions::CloseTarget,
		std::ref(UI_Manager::Get().func)
		, uiText);
	uiImage->AddChild(uiButton);
		


	Reset();
}

void GameState_UI::Destroy()
{	
	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_UI::Reset()
{
}

void GameState_UI::Update()
{
	if ( girl )
	{
		girl->Update();
	}

}

void GameState_UI::Render()
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

void GameState_UI::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_UI::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_UI::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (girl)
	{
		girl->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
