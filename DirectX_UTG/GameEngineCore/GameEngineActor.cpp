#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

// 액터에 컴포넌트 구조 init
void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;                               // 컴포넌트의 액터는 해당 액터로 설정
	_Component->Level = GetLevel();
	_Component->GetTransform()->SetParent(GetTransform());  // 컴포넌트의 부모를 해당 액터로 설정
	_Component->Start();                                    // 컴포넌트 정보 init
}