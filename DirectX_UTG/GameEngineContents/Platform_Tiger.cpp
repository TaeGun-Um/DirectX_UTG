#include "PrecompileHeader.h"
#include "Platform_Tiger.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FrogLevel.h"
#include "You_Died.h"

Platform_Tiger::Platform_Tiger() 
{
}

Platform_Tiger::~Platform_Tiger() 
{
}

void Platform_Tiger::Start()
{

}

void Platform_Tiger::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	PixelCheck(_DeltaTime);
	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Tiger::PixelCheck(float _DeltaTime)
{

}

void Platform_Tiger::MoveDirection(float _DeltaTime)
{

}

void Platform_Tiger::DeathCheck()
{

}