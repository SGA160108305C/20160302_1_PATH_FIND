#pragma once
#include "GameObject.h"
#include "CubeMan.h"
#include "CubeManParts_Light.h"

class CubeMan_Light : public GameObject
{
public:
	CubeMan_Light();
	~CubeMan_Light();

	virtual void Initialize();
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inline const LPD3DXVECTOR3 GetPositionAdress(){ return &position; }

	void SetNextTexture();
				
protected:	
	enum KEY_TYPE
	{
		FORWARD = 0,
		BACKWARD,
		NUM_OF_KEY_TYPE
	};
	D3DXMATRIXA16 world;
	CubeManParts_Light* root = nullptr;
	LPDIRECT3DTEXTURE9 texture[NUM_OF_TEXTURETYPE];
	TextureType currentTexture = TextureType::BATMAN;

	//��ġ�� �̵�, ȸ��, ������
	float moveSpeed = 10.0f;
	float rotationSpeed = 2.0f;
	D3DXVECTOR3 scaleVector = D3DXVECTOR3(1, 1, 1);

	//����
	float jumpPower = 10.0f;
	float jumpTime = 0.0f;
	bool isJumping = false;
	float jumpStart = 0.0f;

	//Ű ����
	bool keyState[NUM_OF_KEY_TYPE];

	//�ִϸ��̼� ó��
	std::map<PartsType, CubeManParts_Light*> animParts;
	void AnimationOnOff(bool on);

	bool GetCubeUVList(D3DXVECTOR2* out, PartsType type);

	//����Ʈ
	D3DMATERIAL9 material;

	D3DLIGHT9 headLight;
	D3DLIGHT9 handLight;	
};

