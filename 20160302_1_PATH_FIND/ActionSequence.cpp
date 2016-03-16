#include "stdafx.h"
#include "ActionSequence.h"


ActionSequence::ActionSequence()
{
}


ActionSequence::~ActionSequence()
{
}

void ActionSequence::AddAction(ActionBase* action)
{
	if (action)
	{
		actionArray.push_back(action);
	}
}

void ActionSequence::Start()
{
	currentIndex = 0;
	if (actionArray.empty())
		return;

	actionArray[currentIndex]->Start();
}

void ActionSequence::Update()
{
	if (currentIndex < actionArray.size())
	{
		actionArray[currentIndex]->Update();
	}
}

void ActionSequence::Destroy()
{
	for (size_t i = 0; i < actionArray.size(); ++i)
	{
		SAFE_DELETE(actionArray[i]);
	}
	actionArray.clear();
}

void ActionSequence::OnActionFinish(ActionBase* sender)
{
	++currentIndex;
	if (currentIndex < actionArray.size())
	{
		actionArray[currentIndex]->Start();
	}
}