#include "PrecompileHeader.h"
#include "Deliver.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Deliver::Deliver() 
{
}

Deliver::~Deliver() 
{
}

void Deliver::Start()
{
	if (nullptr == GameEngineSprite::Find("Deliver"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("1_Ribby_and_Croaks");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Deliver").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->CreateAnimation({ .AnimationName = "Deliver", .SpriteName = "Deliver", .FrameInter = 0.11f, .Loop = true, .ScaleToTexture = true });
		RenderPtr->ChangeAnimation("Deliver");
	}
}

void Deliver::Update(float _DeltaTime)
{
	DirectCheck();
	MoveCalculation(_DeltaTime);
}

void Deliver::DirectCheck()
{
	if (false == Directbool)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
	else
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

void Deliver::MoveCalculation(float _DeltaTime)
{
	if (true == Directbool)
	{
		DelayTime += _DeltaTime;

		if (DelayTime <= 7.0f)
		{
			return;
		}

		MoveTime += _DeltaTime;

		GetTransform()->SetLocalPosition(float4::LerpClamp(StartPostion, EndPostion, MoveTime / 10));

		float4 CurPostion = GetTransform()->GetLocalPosition();
		
		if (EndPostion.x == CurPostion.x)
		{
			Directbool = false;
			MoveTime = 0.0f;
			DelayTime = 0.0f;
		}
	}

	if (false == Directbool)
	{
		DelayTime += _DeltaTime;

		if (DelayTime <= 7.0f)
		{
			return;
		}

		MoveTime += _DeltaTime;

		GetTransform()->SetLocalPosition(float4::LerpClamp(EndPostion, StartPostion, MoveTime / 10));

		float4 CurPostion = GetTransform()->GetLocalPosition();

		if (StartPostion.x == CurPostion.x)
		{
			Directbool = true;
			MoveTime = 0.0f;
			DelayTime = 0.0f;
		}
	}
}