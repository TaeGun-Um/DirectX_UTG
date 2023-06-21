#include "PrecompileHeader.h"
#include "WoodPiece.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "MouseLevel.h"
#include "You_Died.h"

WoodPiece::WoodPiece() 
{
}

WoodPiece::~WoodPiece() 
{
}

void WoodPiece::Start()
{
	/*GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_WoodPiece_Loop").GetFullPath());
	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Object_WoodPiece_Death").GetFullPath());*/

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();

		RenderPtr->CreateAnimation({ .AnimationName = "Object_WoodPiece_Loop", .SpriteName = "Object_WoodPiece_Loop", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->CreateAnimation({ .AnimationName = "Object_WoodPiece_Death", .SpriteName = "Object_WoodPiece_Death", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

		RenderPtr->ChangeAnimation("Object_WoodPiece_Loop");
		ChangeState(WoodPieceState::Loop);
	}

	if (nullptr == ProjectileCollisionPtr)
	{
		ProjectileCollisionPtr = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::MonsterAttack));
		ProjectileCollisionPtr->SetColType(ColType::SPHERE2D);
		ProjectileCollisionPtr->GetTransform()->SetLocalScale({ 55, 55, 1 });
		ProjectileCollisionPtr->GetTransform()->SetLocalPosition({ 0, 0 });
	}

	if (nullptr == ProjectileCollisionRenderPtr)
	{
		ProjectileCollisionRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		ProjectileCollisionRenderPtr->SetTexture("GreenBox.png");
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalScale(ProjectileCollisionPtr->GetTransform()->GetLocalScale());
		ProjectileCollisionRenderPtr->GetTransform()->SetLocalPosition(ProjectileCollisionPtr->GetTransform()->GetLocalPosition());
		ProjectileCollisionRenderPtr->Off();
	}
}

void WoodPiece::Update(float _DeltaTime)
{
	if (true == MouseLevel::MouseLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	MoveDirection(_DeltaTime);
	PixelCheck(_DeltaTime);
	UpdateState(_DeltaTime);
}

void WoodPiece::MoveDirection(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	if (MoveDirect.y >= -800.0f)
	{
		MoveDirect.y -= 1100.0f * _DeltaTime;
	}

	GetTransform()->AddLocalPosition(MoveDirect * _DeltaTime);
}

void WoodPiece::PixelCheck(float _DeltaTime)
{
	if (true == IsDeath)
	{
		return;
	}

	float4 ProjectilePos = GetTransform()->GetWorldPosition();
	float4 LandPos = ProjectilePos + float4{ 0, -20 };

	GameEnginePixelColor LandPixel = PixelCollisionCheck.PixelCheck(LandPos);

	if (true == PixelCollisionCheck.IsBlack(LandPixel))
	{
		MoveDirect = float4::Zero;
		IsDeath = true;
	}
}

void WoodPiece::ChangeState(WoodPieceState _StateValue)
{
	WoodPieceState NextState = _StateValue;
	WoodPieceState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case WoodPieceState::Loop:
		LoopStart();
		break;
	case WoodPieceState::Death:
		DeathStart();
		break;
	default:
		break;
	}

	switch (NextState)
	{
	case WoodPieceState::Loop:
		LoopEnd();
		break;
	case WoodPieceState::Death:
		DeathEnd();
			break;
	default:
		break;
	}
}
void WoodPiece::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case WoodPieceState::Loop:
		LoopUpdate(_DeltaTime);
		break;
	case WoodPieceState::Death:
		DeathUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void WoodPiece::LoopStart()
{
	RenderPtr->ChangeAnimation("Object_WoodPiece_Loop");
}
void WoodPiece::LoopUpdate(float _DeltaTime)
{
	if (true == IsDeath)
	{
		ProjectileCollisionPtr->Off();
		ProjectileCollisionRenderPtr->Off();
		ChangeState(WoodPieceState::Death);
		return;
	}
}
void WoodPiece::LoopEnd()
{

}

void WoodPiece::DeathStart()
{
	RenderPtr->ChangeAnimation("Object_WoodPiece_Death");
}
void WoodPiece::DeathUpdate(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		Death();
	}
}
void WoodPiece::DeathEnd()
{

}