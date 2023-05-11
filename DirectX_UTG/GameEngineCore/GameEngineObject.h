#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// �Ҹ��ڿ� virtual���̴� ���� => �ڽļҸ��ڰ� ����� ȣ��ǰ� �ϱ� ���ؼ�
// ���������Լ� ���� ���� => �ڽĿ��� �������̽��� �����ϱ� ���ؼ�
// ���������Լ� ���� ���� => �� Ŭ������ ��üȭ �Ҽ� ���� ����� ���ؼ�.
// �Ҹ��ڸ� ���������Լ��� ����� ����? => �߻�ȭ �Ҹ��Ѱ� ���� ���.

// ���� : ���߻�� Ŭ����, ���ϱ���(Transform) ����� ���� Ŭ����
class GameEngineObject :
	public GameEngineObjectBase,
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject> // ħ���� ptr
	// shared_ptr�� ���۷��� ī��Ʈ�� �ڽ��� ������ �ֱ� ������, new ������ �߻��ϰ� �ȴ�.
	// ����� ����ϴ� ���, �θ� ���۷��� ī��Ʈ�� ���ϰ� �ִٸ� new ������ ���� �� �ִ�.
	// �̶� Ȱ���ϴ� ���� std::enable_shared_from_this
{
	friend class GameEngineComponent;
	friend class GameEngineActor;
	friend class GameEngineTransform;
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// ����� Ŭ������ Transform ����
	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}

	// shared_ptr ����
	template<typename PtrType>
	std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	{
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}

	virtual void AccLiveTime(float _LiveTime)
	{
		LiveTime += _LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Release();

	void PushChild(std::shared_ptr<GameEngineObject> _Child)
	{
		Childs.push_back(_Child);
	}

private:
	float LiveTime = 0.0f;
	GameEngineTransform Transform; // Object�� ��ӹ��� Ŭ������ ��� Transform�� ���´�.
	std::list<std::shared_ptr<GameEngineObject>> Childs;
	class GameEngineLevel* Level;

	void AllAccTime(float _DeltaTime);
	void AllUpdate(float _DeltaTime);
	void AllRender(float _DeltaTime);
	void AllRelease();
};
