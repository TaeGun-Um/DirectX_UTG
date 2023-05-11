#pragma once
#include "GameEngineUpdateObject.h"
#include <GameEngineBase\GameEngineTimeEvent.h>
#include <string_view>
#include <map>

// ���� : ����
class GameEngineActor;
class GameEngineCamera;
class GameEngineLevel : public GameEngineUpdateObject
{
	friend class GameEngineTransform;
	friend class GameEngineCore;

public:
	GameEngineTimeEvent TimeEvent;

	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// string �Ű� ������ Ȱ���� CreateActor
	template<typename ActorType >
	std::shared_ptr<ActorType> CreateActor(const std::string_view& _Name)
	{
		return CreateActor<ActorType>(0, _Name);
	}

	// Order ����, string �Ű� ������ ���� CreateActor
	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();

		std::string Name = _Name.data();

		if (_Name == "")
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		ActorInit(NewActor, _Order, this);

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	// ������ ���� ī�޶� ����
	std::shared_ptr<class GameEngineCamera> GetMainCamera()
	{
		return MainCamera;
	}

	// (05.03)GUI���� ������ ���̳���ĳ��Ʈ ����������
	std::shared_ptr<GameEngineLevel> GetSharedThis()
	{
		return Shared_This_dynamic_pointer<GameEngineLevel>();
	}

protected:
	virtual void Start() = 0;
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

	virtual void LevelChangeStart();
	virtual void LevelChangeEnd();

private:
	std::shared_ptr<GameEngineCamera> MainCamera;                       // ���� ī�޶�, ���� ���� �� �����ڿ��� ������
	std::shared_ptr<GameEngineCamera> UICamera;                         // UI ī�޶�, ���� �ȸ���

	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;  // ������ ���ԵǴ� Actor���� ����Ʈ

	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);

	void ActorUpdate(float _DeltaTime);
	void ActorRender(float _DeltaTime);
	void ActorRelease();
};

