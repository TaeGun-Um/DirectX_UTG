#include "PrecompileHeader.h"
#include "Obj.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

Obj::Obj() 
{
}

Obj::~Obj() 
{
}

void Obj::Update(float _DeltaTime)
{

}

void Obj::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
}