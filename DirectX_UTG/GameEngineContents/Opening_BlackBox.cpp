#include "PrecompileHeader.h"
#include "Opening_BlackBox.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "MDHR_Logo.h"

Opening_BlackBox::Opening_BlackBox() 
{
}

Opening_BlackBox::~Opening_BlackBox() 
{
}

void Opening_BlackBox::Start()
{
	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineUIRenderer>();
		RenderPtr->SetTexture("BlackBox.png");
		RenderPtr->GetTransform()->SetLocalScale({ 1340, 800 });
	}
}
void Opening_BlackBox::Update(float _DeltaTime)
{
	if (false == IsBGMOn)
	{
		IsBGMOn = true;
		BGMPlayer = GameEngineSound::Play("Optical_Start_001.wav");
	}

	DelayTime += _DeltaTime;

	if (3.0f <= DelayTime && false == IsLogoBGM)
	{
		IsLogoBGM = true;
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::Play("MDHR_LOGO_STING.wav");
	}

	if (3.5f >= DelayTime)
	{
		return;
	}
	else
	{
		MDHR_Logo::LogoPtr->On();
	}

	RenderPtr->ColorOptionValue.MulColor.a -= _DeltaTime;

	if (RenderPtr->ColorOptionValue.MulColor.a <= 0.0f)
	{
		IsEnd = true;
		RenderPtr->Off();
	}
}