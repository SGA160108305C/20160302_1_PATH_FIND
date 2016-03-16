#pragma once
#include "UI_Base.h"
#include "UI_Functions.h"
#include "UI_Text.h"
#include "UI_Image.h"
#include "UI_Button.h"

class UI_Manager
{
private:
	UI_Manager();
	UI_Manager(const UI_Manager& other);
	~UI_Manager();

public :
	static UI_Manager& Get()
	{
		static UI_Manager instance;
		return instance;
	}

	virtual void Initialize();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();
	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static inline LPD3DXSPRITE GetSprite(){ 
		return UI_Manager::Get().GetInstanceSprite(); }
	inline UI_Base* GetRoot(){ return root; }
	inline void SetRoot(UI_Base* ui){ root = ui; }

	UI_Functions func;


protected:
	LPD3DXSPRITE sprite = nullptr;
	UI_Base* root = nullptr;

	inline LPD3DXSPRITE GetInstanceSprite(){ return sprite; }
};

