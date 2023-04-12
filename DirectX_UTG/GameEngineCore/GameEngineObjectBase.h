#pragma once
#include <list>
#include <memory>
#include <string_view>

// ���� : Object���� �⺻ ��ɵ��� ����ϴ� Ŭ����
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
	
	// ����� Object�� Order ����
	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// ����� Object�� Order ����
	int GetOrder()
	{
		return Order;
	}

	// ����� Object �������� On
	void On()
	{
		ActiveValue = true;
	}

	// ����� Object�� �������� Off
	void Off()
	{
		ActiveValue = false;
	}

	// ����� Object�� Death ó��
	void Death()
	{
		DeathValue = true;
	}

	// ����� Object�� ����׹�� On
	void DebugOn()
	{
		DebugValue = true;
	}

	// ����� Object�� ����׹���� On���� Ȯ��
	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool ActiveValue = true; // ������ ������
	bool DeathValue = false; // �׾��� ��Ҵ�
	bool DebugValue = false; // ����׹��
	int Order = 0;           // Object�� ����
	
};

