#include "PrecompileHeader.h"
#include "PlayerGhost.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

PlayerGhost::PlayerGhost() 
{
}

PlayerGhost::~PlayerGhost() 
{
}

void PlayerGhost::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Ghost", .SpriteName = "Ghost", .FrameInter = 0.05f, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Ghost");
	}
}

void PlayerGhost::Update(float _DeltaTime)
{
	DeathCheck();

	GetTransform()->AddLocalPosition({0, MoveSpeed * _DeltaTime });

}

void PlayerGhost::DeathCheck()
{
	if (StartPosition.y + 700 <= GetTransform()->GetLocalPosition().y)
	{
		Death();
	}
}