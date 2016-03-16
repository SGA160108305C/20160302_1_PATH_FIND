#include "stdafx.h"
#include "UI_Manager.h"


UI_Manager::UI_Manager()
{
}


UI_Manager::~UI_Manager()
{
}

void UI_Manager::Initialize()
{
	D3DXCreateSprite(
		GameManager::GetDevice(), 
		&sprite);
}
void UI_Manager::Destroy()
{
	SAFE_RELEASE(sprite);

	SAFE_DELETE(root);
}

void UI_Manager::Update()
{
	if (root)
	{
		root->Update();
	}
}

void UI_Manager::Render()
{
	if (root)
	{
		root->Render();
	}
}

LRESULT UI_Manager::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (root)
	{
		result = root->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}