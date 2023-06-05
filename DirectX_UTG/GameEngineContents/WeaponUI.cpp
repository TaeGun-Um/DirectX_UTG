#include "PrecompileHeader.h"
#include "WeaponUI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "Player.h"

WeaponUI::WeaponUI() 
{
}

WeaponUI::~WeaponUI() 
{
}

void WeaponUI::SetMainPalyer(std::shared_ptr<class Player> _MainPlayer)
{
	MainPlayer = _MainPlayer;
}

void WeaponUI::Start()
{
	if (nullptr == GameEngineTexture::Find("Health.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("PeashooterUI.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("SpreadUI.png").GetFullPath());
	}

	PeashooterRenderPtr = CreateComponent<GameEngineUIRenderer>();
	SpreadRenderPtr = CreateComponent<GameEngineUIRenderer>();

	PeashooterRenderPtr->GetTransform()->SetLocalScale({ 55, 55 });
	SpreadRenderPtr->GetTransform()->SetLocalScale({ 55, 55 });

	PeashooterRenderPtr->SetTexture("PeashooterUI.png");
	SpreadRenderPtr->SetTexture("SpreadUI.png");

	PeashooterRenderPtr->Off();
	SpreadRenderPtr->Off();
}

void WeaponUI::Update(float _DeltaTime)
{
	if (true == MainPlayer->IsWeaponChange)
	{
		MainPlayer->IsWeaponChange = false;

		if (true == MainPlayer->WeaponType)
		{
			PeashooterAnimation = true;
			SpreadAnimation = false;
		}
		else
		{
			PeashooterAnimation = false;
			SpreadAnimation = true;
		}

		GetTransform()->SetLocalPosition(StartPosition);
		MoveDistance = float4::Zero;
		DelayTime = 0.0f;
		RenderOut = false;
	}

	CurPosition = GetTransform()->GetLocalPosition();
	float4 Movedir = float4::Zero;

	if (true == PeashooterAnimation)
	{
		PeashooterRenderPtr->On();
		SpreadRenderPtr->Off();
	}
	else if (true == SpreadAnimation)
	{
		PeashooterRenderPtr->Off();
		SpreadRenderPtr->On();
	}

	if (true == PeashooterRenderPtr->IsUpdate()
		|| true == SpreadRenderPtr->IsUpdate())
	{
		Movedir = (EndPosition - CurPosition);

		MoveDistance = Movedir * 3.0f * _DeltaTime;

		GetTransform()->AddWorldPosition(MoveDistance);

		if ((EndPosition.y - 10) <= CurPosition.y)
		{
			RenderOut = true;
			DelayTime += _DeltaTime;
		}
	}

	if (true == RenderOut && 1.0f <= DelayTime)
	{
		Movedir = ((StartPosition + float4{0, -50}) - CurPosition);

		MoveDistance = Movedir * 3.0f * _DeltaTime;

		GetTransform()->AddWorldPosition(MoveDistance);

		if ((StartPosition + float4{ 0, 9 }).y >= CurPosition.y)
		{
			PeashooterRenderPtr->Off();
			SpreadRenderPtr->Off();
		}
	}
}