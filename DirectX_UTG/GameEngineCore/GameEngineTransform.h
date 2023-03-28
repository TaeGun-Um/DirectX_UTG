#pragma once
#include <list>
#include <GameEngineBase/GameEngineMath.h>

// ���� : Ư���� ��ü�� ũ��, �̵�, ȸ���� ���õǴ� ���� �Ӽ����� �������ִ� Ŭ����
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	// ��� ��� ��ȯ ����� ��� TransformUpdate()�� ȣ���Ͽ� ����ǵ��� �Ѵ�.
	// ���� �����ϸ� ����� ��ü ����� ��� ����Ǵ� �����̴�.
	// ������� �ٷ� Ȯ���� �� �־, ������ �������̴�.
	// ������ ������Ʈ ���鶩 �̰� ����
	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;
		TransformUpdate();
	}

	void AddLocalScale(const float4& _Value)
	{
		LocalScale += _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const float4& _Value)
	{
		LocalRotation += _Value;
		TransformUpdate();
	}

	void AddLocalPosition(const float4& _Value)
	{
		LocalPosition += _Value;
		TransformUpdate();
	}

	// LocalWorldMatrix�� ���Ϳ� ����� ��� ������̴�.
	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	// Ȥ�ó� �� ����ȭ�� ���� ���۷����� ����
	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

protected:

private:
	void TransformUpdate();

	// weak_ptr ����, �Ŀ� �� ����
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	float4 LocalScale = float4::One;      // ũ��� 0�̸� ��ȯ�� �ȵǱ� ������, �����͸� Ȱ���Ѵ�.
	float4 LocalRotation = float4::Zero;  // �������� ���κ���
	float4 LocalPosition = float4::Zero;

	float4x4 LocalScaleMatrix;            // ũ�� ��ȯ ���
	float4x4 LocalRotationMatrix;         // ȸ�� ��ȯ ���
	float4x4 LocalPositionMatrix;         // �̵� ��ȯ ���

	float4x4 LocalWorldMatrix;
};

