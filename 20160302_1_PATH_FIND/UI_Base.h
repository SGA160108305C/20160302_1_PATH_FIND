#pragma once
class UI_Base
{
public:
	UI_Base();
	virtual ~UI_Base();

	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void AddChild(UI_Base* child);
	virtual UI_Base* GetChildByID(int childID);

	inline const D3DXMATRIXA16& GetWorld(){ return world; }
	inline int GetID(){ return id; }
	inline D3DXVECTOR2& GetSize(){ return size; }

	inline void SetPosition(float x, float y, float z){ position = D3DXVECTOR3(x, y, z); }
	inline void SetSize(float width, float height){ size.x = width; size.y = height; }
	inline void SetID(int _ID){ id = _ID; }
	inline void SetShow(bool show = true){ isShow = show; }

protected:
	D3DXMATRIXA16 world;
	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR2 size = D3DXVECTOR2(0, 0);

	const int ID_EMPTY = -1;
	int id = ID_EMPTY;	//-1이면 세팅안된것

	bool isShow = true;

	UI_Base* parent = nullptr;
	std::vector<UI_Base*> childArray;

	inline void SetParent(UI_Base* _parent){ parent = _parent; }
};

