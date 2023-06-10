#include "PrecompileHeader.h"
#include "Platform_Bison.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FrogLevel.h"
#include "You_Died.h"

Platform_Bison::Platform_Bison() 
{
}

Platform_Bison::~Platform_Bison() 
{
}

void Platform_Bison::Start()
{

}

void Platform_Bison::Update(float _DeltaTime)
{
	if (true == FrogLevel::FrogLevelPtr->GetYouDiedPtr()->GetIsEnd())
	{
		Death();
	}

	MoveDirection(_DeltaTime);
	DeathCheck();
}

void Platform_Bison::MoveDirection(float _DeltaTime)
{

}

void Platform_Bison::DeathCheck()
{

}