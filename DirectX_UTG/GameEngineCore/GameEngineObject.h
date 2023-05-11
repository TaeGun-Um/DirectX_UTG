#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// 소멸자에 virtual붙이는 이유 => 자식소멸자가 제대로 호출되게 하기 위해서
// 순수가상함수 쓰는 이유 => 자식에게 인터페이스를 강요하기 위해서
// 순수가상함수 쓰는 이유 => 그 클래스를 객체화 할수 없게 만들기 위해서.
// 소멸자를 순수가상함수를 만드는 이유? => 추상화 할만한게 딱히 없어서.

// 설명 : 다중상속 클래스, 기하구조(Transform) 상속을 위한 클래스
class GameEngineObject :
	public GameEngineObjectBase,
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject> // 침습형 ptr
	// shared_ptr은 래퍼런스 카운트를 자신이 가지고 있기 때문에, new 연산이 발생하게 된다.
	// 상속을 사용하는 경우, 부모가 레퍼런스 카운트를 지니고 있다면 new 연산을 줄일 수 있다.
	// 이때 활용하는 것이 std::enable_shared_from_this
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

	// 상속한 클래스의 Transform 리턴
	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}

	// shared_ptr 리턴
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
	GameEngineTransform Transform; // Object를 상속받은 클래스는 모두 Transform을 갖는다.
	std::list<std::shared_ptr<GameEngineObject>> Childs;
	class GameEngineLevel* Level;

	void AllAccTime(float _DeltaTime);
	void AllUpdate(float _DeltaTime);
	void AllRender(float _DeltaTime);
	void AllRelease();
};
