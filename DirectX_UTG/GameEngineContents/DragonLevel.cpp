#include "PrecompileHeader.h"
#include "DragonLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

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

}

void DragonLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

}
void DragonLevel::LevelChangeEnd()
{

}