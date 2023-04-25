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
		UpdateValue = true;
	}

	// ����� Object�� �������� Off
	void Off()
	{
		UpdateValue = false;
	}

	// ����� Object�� Death ó��
	void Death()
	{
		DeathValue = true;
	}

	// ���Ͱ� �׾����� üũ, �θ��ڽİ��� ���踦 �ľ��ϱ� ���� virtual
	virtual bool IsDeath()
	{
		return DeathValue;
	}

	// ������Ʈ�� on���� üũ, �θ��ڽİ��� ���踦 �ľ��ϱ� ���� virtual
	virtual bool IsUpdate()
	{
		return UpdateValue;
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
	bool UpdateValue = true; // ������ ������
	bool DeathValue = false; // �׾��� ��Ҵ�
	bool DebugValue = false; // ����׹��
	int Order = 0;           // Object�� ����
	
};

