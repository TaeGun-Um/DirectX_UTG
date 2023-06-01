#include "PrecompileHeader.h"
#include "HealthUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

HealthUI::HealthUI() 
{
}

HealthUI::~HealthUI() 
{
}

void HealthUI::SetMainPalyer(std::shared_ptr<class Player> _MainPalyer)
{
	MainPalyer = _MainPalyer;
}

void HealthUI::Start()
{
	if (nullptr == GameEngineSprite::Find("CardUI"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CardUI").GetFullPath());
	}
}

void HealthUI::Update(float _DeltaTime)
{

}