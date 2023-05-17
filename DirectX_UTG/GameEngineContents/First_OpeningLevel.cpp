#include "PrecompileHeader.h"
#include "First_OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Second_OpeningLevel.h"
#include "Screen_FX.h"
#include "MDHR_Logo.h"
#include "Title_Background.h"

First_OpeningLevel::First_OpeningLevel() 
{
}

First_OpeningLevel::~First_OpeningLevel() 
{
}

void First_OpeningLevel::Start()
{
	// 리소스 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Opening1");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });

	// CreateActor
	//std::shared_ptr<MDHR_Logo> Object0 = CreateActor<MDHR_Logo>("Screen_FX");
	// std::shared_ptr<MDHR_Logo> Object2 = CreateActor<MDHR_Logo>("MDHR_Logo"); // 스프라이트 시트
	std::shared_ptr<Title_Background> Object1 = CreateActor<Title_Background>();
	Object1->GetTransform()->AddWorldPosition({ 0, -3 });
}
void First_OpeningLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Action"))
	{
		GameEngineCore::CreateLevel<Second_OpeningLevel>();
		GameEngineCore::ChangeLevel("Second_OpeningLevel");
	}
}

void First_OpeningLevel::LevelChangeStart()
{

}
void First_OpeningLevel::LevelChangeEnd()
{
}