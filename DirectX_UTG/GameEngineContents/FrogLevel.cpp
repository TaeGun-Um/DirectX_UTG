#include "PrecompileHeader.h"
#include "FrogLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

FrogLevel::FrogLevel() 
{
}

FrogLevel::~FrogLevel() 
{
}

void FrogLevel::Start()
{

}
void FrogLevel::Update(float _DeltaTime)
{

}

void FrogLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

}
void FrogLevel::LevelChangeEnd()
{

}