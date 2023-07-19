#include "PrecompileHeader.h"
#include "Ready_Wallop.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

Ready_Wallop::Ready_Wallop() 
{
}

Ready_Wallop::~Ready_Wallop() 
{
}

void Ready_Wallop::Start()
{
	if (nullptr == GameEngineSprite::Find("Ready_WALLOP"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->GetTransform()->SetLocalScale({ 1280, 720 });
		RenderPtr->CreateAnimation({ .AnimationName = "Ready_Wallop", .SpriteName = "Ready_Wallop", .FrameInter = 0.05f, .Loop = false });

		RenderPtr->ChangeAnimation("Ready_Wallop");
		RenderPtr->Off();
	}

	RenderPtr->SetAnimationStartEvent("Ready_Wallop", 20, std::bind(&Ready_Wallop::EndVoiceSound, this));
}

void Ready_Wallop::Update(float _DeltaTime)
{
	if (true == RenderPtr->IsAnimationEnd())
	{
		IsEnd = true;
		RenderPtr->Off();
	}
}

void Ready_Wallop::StartVoiceSound()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (0 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
	else if (1 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
	else if (2 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_Start_A.wav");
	}
}

void Ready_Wallop::EndVoiceSound()
{
	int RandC = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (0 == RandC)
	{
		VoicePlayer = GameEngineSound::Play("announcer_End_A.wav");
	}
	else
	{
		VoicePlayer = GameEngineSound::Play("announcer_End_B.wav");
	}
}