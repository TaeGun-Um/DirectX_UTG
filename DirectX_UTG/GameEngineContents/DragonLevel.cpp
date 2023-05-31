#include "PrecompileHeader.h"
#include "DragonLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GrimMatchstick.h"
#include "TestActor.h"

DragonLevel::DragonLevel() 
{
}

DragonLevel::~DragonLevel() 
{
}

void DragonLevel::Start()
{

}
void DragonLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NextLevel"))
	{
		GameEngineCore::ChangeLevel("MouseLevel");
	}
}

void DragonLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

	{
		if (nullptr == DragonObject)
		{
			DragonObject = CreateActor<GrimMatchstick>();
		}
	}

	GameEngineSprite::ReLoad("Dragon_Idle");
}

void DragonLevel::LevelChangeEnd()
{
	if (nullptr != GameEngineSprite::Find("Dragon_Idle"))
	{
		GameEngineSprite::UnLoad("Dragon_Idle");
	}
}