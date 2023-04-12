#pragma once
#include <list>
#include <memory>
#include <string_view>

// 설명 : Object들의 기본 기능들을 담당하는 클래스
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	~GameEngineObjectBase();

	// delete Function
	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;
	
	// 상속한 Object의 Order 세팅
	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// 상속한 Object의 Order 리턴
	int GetOrder()
	{
		return Order;
	}

	// 상속한 Object 랜더상태 On
	void On()
	{
		ActiveValue = true;
	}

	// 상속한 Object의 랜더상태 Off
	void Off()
	{
		ActiveValue = false;
	}

	// 상속한 Object를 Death 처리
	void Death()
	{
		DeathValue = true;
	}

	// 상속한 Object의 디버그밸류 On
	void DebugOn()
	{
		DebugValue = true;
	}

	// 상속한 Object의 디버그밸류가 On인지 확인
	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool ActiveValue = true; // 켜졌다 꺼졌다
	bool DeathValue = false; // 죽었다 살았다
	bool DebugValue = false; // 디버그밸류
	int Order = 0;           // Object의 오더
	
};

