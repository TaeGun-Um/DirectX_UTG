#include "PrecompileHeader.h"
#include "MouseLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

MouseLevel::MouseLevel() 
{
}

MouseLevel::~MouseLevel() 
{
}

void MouseLevel::Start()
{

}
void MouseLevel::Update(float _DeltaTime)
{

}

void MouseLevel::LevelChangeStart()
{
	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -620.0f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);

}
void MouseLevel::LevelChangeEnd()
{

}