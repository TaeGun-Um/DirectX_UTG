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
{
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

private:
	GameEngineTransform Transform; // Object�� ��ӹ��� Ŭ������ ��� Transform�� ���´�.

};
