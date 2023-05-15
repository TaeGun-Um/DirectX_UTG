#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

// ���Ϳ� ������Ʈ ���� init
void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component, int _Order)
{
	_Component->Actor = this;										 // ������Ʈ�� ���ʹ� �ش� ���ͷ� ����
	_Component->Level = GetLevel();
	_Component->GetTransform()->SetParent(GetTransform(), false);    // ������Ʈ�� �θ� �ش� ���ͷ� ����
	_Component->SetOrder(_Order);
	_Component->Start();											 // ������Ʈ ���� init

	// PushChild(_Component); << SetParent ������ child�� �� �� ���� ��
}

void GameEngineActor::SetOrder(int _Order)
{

	std::shared_ptr<GameEngineActor> ConThis = DynamicThis<GameEngineActor>();

	// ������ �׷쿡�� ���� �����
	std::list<std::shared_ptr<GameEngineActor>>& Group = GetLevel()->Actors[GetOrder()];
	Group.remove(ConThis);

	GameEngineObjectBase::SetOrder(_Order);

	// ���ο� �׷쿡 ���� �߰��Ѵ�.
	GetLevel()->Actors[GetOrder()].push_back(ConThis);

}