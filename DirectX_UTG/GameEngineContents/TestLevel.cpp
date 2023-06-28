#include "PrecompileHeader.h"
#include "TestLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "HourGlass.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{

}
void TestLevel::Update(float _DeltaTime)
{

}

void TestLevel::LevelChangeStart()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition(ScreenSize + float4{ 0, 0, -620.0f });

	// CreateActor
	{
		std::shared_ptr<HourGlass> HourObject = CreateActor<HourGlass>();
		HourObject->GetTransform()->SetLocalPosition(ScreenSize + float4{ 0 , 0, -10.0f });
	}

}
void TestLevel::LevelChangeEnd()
{
}