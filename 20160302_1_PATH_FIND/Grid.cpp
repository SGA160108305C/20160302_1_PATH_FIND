#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
}


Grid::~Grid()
{
	Destroy();
}

void Grid::Initialize(
	int lineCount /*= 30*/, 
	float interval/* = 1.0f*/)
{
	int halfLineCount = (int)(lineCount * 0.5f);
	float max = halfLineCount * interval;
	
	//바닥 피킹용
	groundVertex.resize(6);
	groundVertex[0] = D3DXVECTOR3(-max, 0, -max);
	groundVertex[1] = D3DXVECTOR3(-max, 0, max);
	groundVertex[2] = D3DXVECTOR3(max, 0, max);
	groundVertex[3] = D3DXVECTOR3(-max, 0, -max);
	groundVertex[4] = D3DXVECTOR3(max, 0, max);
	groundVertex[5] = D3DXVECTOR3(max, 0, -max);

	ZeroMemory(&groundMaterial, sizeof(D3DMATERIAL9));
	groundMaterial.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	groundMaterial.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	groundMaterial.Specular= D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);


	//일반 줄
	D3DCOLOR color = 0;
	for (int i = 1; i <= halfLineCount; ++i)
	{
		if ( ( i ) % 5 == 0 )
		{
			color = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			color = D3DCOLOR_XRGB(128, 128, 128);
		}

		vertices.push_back(FVF_PositionColor(D3DXVECTOR3(max, 0.01f, (float)(-i)), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3(-max, 0.01f, (float)(-i)), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3(max, 0.01f, (float)(i)), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3(-max, 0.01f, (float)(i)), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3((float)(i), 0.01f, max), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3((float)(i), 0.01f, -max), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3((float)(-i), 0.01f, max), color));
		vertices.push_back(FVF_PositionColor(D3DXVECTOR3((float)(-i), 0.01f, -max), color));
	}

	//축
	D3DXMATRIXA16 axisWorld, axisScale, axisRotation, axisPos;
	D3DXMatrixScaling(&axisScale, 0.3f, 2.0f, 0.3f);

	color = D3DCOLOR_XRGB(255, 0, 0);
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(max, 0.01f, 0.0f), color));
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(-max, 0.01f, 0.0f), color));

	color = D3DCOLOR_XRGB(0, 255, 0);
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(0.0f, max, 0.0f), color));
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(0.0f, -max, 0.0f), color));

	color = D3DCOLOR_XRGB(0, 0, 255);
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(0.0f, 0.01f, max), color));
	vertices.push_back(FVF_PositionColor(D3DXVECTOR3(0.0f, 0.01f, -max), color));
	
	D3DXMatrixIdentity(&world);
}

void Grid::Destroy()
{
}

void Grid::Render()
{	
	GameManager::GetDevice()->SetTexture(0, nullptr);

	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);	

	//지면 표시
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	GameManager::GetDevice()->SetFVF(FVF_Position::FVF);
	GameManager::GetDevice()->SetMaterial(&groundMaterial);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		2,
		&groundVertex[0],
		sizeof(FVF_Position));


	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	GameManager::GetDevice()->SetFVF(FVF_PositionColor::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,
		(int)(vertices.size() * 0.5f),
		&vertices[0],
		sizeof(FVF_PositionColor));
}
