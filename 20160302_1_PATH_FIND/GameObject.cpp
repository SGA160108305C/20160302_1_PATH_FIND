#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{

}

void GameObject::Destroy()
{
	SAFE_DELETE(action);
}

void GameObject::Update()
{
	if (action)
	{
		action->Update();
	}
}