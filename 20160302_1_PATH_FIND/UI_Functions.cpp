#include "stdafx.h"
#include "UI_Functions.h"


UI_Functions::UI_Functions()
{
}


UI_Functions::~UI_Functions()
{
}

void UI_Functions::ClickTest()
{
	UI_Manager::Get().GetRoot()->SetShow(false);
}

void UI_Functions::CloseTarget(UI_Base* target)
{
	if (target)
	{
		target->SetShow(false);
	}
}