#include "stdafx.h"
#include "UI_Base.h"


UI_Base::UI_Base()
{
	D3DXMatrixIdentity(&world);
}

UI_Base::~UI_Base()
{
}

void UI_Base::Destroy()
{
	parent = nullptr;
	for (auto iter = childArray.begin(); iter != childArray.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	childArray.clear();
}

void UI_Base::Update()
{
	if (isShow != true)
	{
		return;
	}

	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);

	if (parent)
	{
		world *= parent->GetWorld();
	}
	for (auto iter = childArray.begin(); iter != childArray.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void UI_Base::Render()
{
	if (isShow != true)
	{
		return;
	}
	for (auto iter = childArray.begin(); iter != childArray.end(); ++iter)
	{
		(*iter)->Render();
	}
}

LRESULT UI_Base::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (isShow != true)
	{
		return result;
	}
	
	for (auto iter = childArray.begin(); iter != childArray.end(); ++iter)
	{
		result = (*iter)->InputProc(hWnd, message, wParam, lParam);
		if (result != 0)
		{
			break;
		}
	}
	return result;
}

void UI_Base::AddChild(UI_Base* child)
{
	if (child)
	{
		child->SetParent(this);
		childArray.push_back(child);
	}
}

UI_Base* UI_Base::GetChildByID(int childID)
{
	UI_Base* child = nullptr;

	if (childID < (int)childArray.size() && childID >= 0)
	{
		child = childArray[childID];
	}

	return child;
}