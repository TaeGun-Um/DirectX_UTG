#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// ���� : Ư���� ��ü�� ũ�� ȸ�� �̵��� ���õ� ���ϼӼ��� �������ش�.
class GameEngineTransform : public GameEngineObjectBase
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

	// ���� ũ�� ����
	void SetWorldScale(const float4& _Value)
	{
		WorldScale = _Value;

		if (nullptr == Parent)
		{
			LocalScale = WorldScale;
		}
		else
		{
			LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ��ġ ����
	void SetWorldRotation(const float4& _Value)
	{
		if (true == IsDebug())
		{
			int a = 0;
		}

		WorldRotation = _Value;

		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}
		else
		{
			float4 Rot = Parent->GetWorldRotation();
			LocalRotation = WorldRotation - Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;

		if (nullptr == Parent)
		{
			LocalPosition = WorldPosition;
		}
		else
		{
			LocalPosition = WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ũ�� ��� ����
	float4 GetWorldScale()
	{
		return WorldScale;
	}

	// ���� ȸ�� ��� ����
	float4 GetWorldRotation()
	{
		return WorldRotation;
	}

	// ���� �̵� ��� ����
	float4 GetWorldPosition()
	{
		return WorldPosition;
	}

	// ���� ũ�� ����
	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;

		if (nullptr == Parent)
		{
			WorldScale = LocalScale;
		}
		else
		{
			WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ȸ�� ����
	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;

		if (nullptr == Parent)
		{
			WorldRotation = LocalRotation;
		}
		else
		{
			WorldRotation = LocalRotation + Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;

		if (nullptr == Parent)
		{
			WorldPosition = LocalPosition;
		}
		else
		{
			WorldPosition = LocalPosition * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ũ�� ��� ����
	float4 GetLocalScale()
	{
		return LocalScale;
	}

	// ���� ȸ�� ��� ����
	float4 GetLocalRotation()
	{
		return LocalRotation;
	}

	// ���� �̵� ��� ����
	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	// ���� ��� ����
	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	// ���� ��� ����(���۷���)
	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	// ���ÿ��� ��� ����
	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	// ���ÿ��� ��� ����(���۷���)
	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	// ���� ũ�� Add
	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(LocalScale + _Value);
	}

	// ���� ȸ�� Add
	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(LocalRotation + _Value);
	}

	// ���� �̵� Add
	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(LocalPosition + _Value);
	}

	// ���忡�� �ڽ��� �ٶ󺸴� ���� ���� ������������ ����
	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// ���忡�� �ڽ��� ���� ���ϴ� ���� ������������ ����
	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// ���忡�� �ڽ��� ������ ���� ������������ ����
	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// ���ÿ��� �ڽ��� �ٶ󺸴� ���� ���� ������������ ����
	float4 GetLocalForwardVector()
	{
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// ���ÿ��� �ڽ��� ���� ���ϴ� ���� ������������ ����
	float4 GetLocalUpVector()
	{
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// ���ÿ��� �ڽ��� ������ ���� ������������ ����
	float4 GetLocalRightVector()
	{
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// ���� �������� ��� ����
	const float4x4 GetWorldViewProjectionMatrix()
	{
		return WorldViewProjectionMatrix;
	}

	// ���� �������� ��� ����(���۷���)
	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return WorldViewProjectionMatrix;
	}

	// ī�޶� ���(��, ��������) ����
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		View = _View;
		Projection = _Projection;
		WorldViewProjectionMatrix = WorldMatrix * View * Projection;
	}

	// ī�޶� ���(����Ʈ) ����
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		ViewPort = _ViewPort;
		WorldViewProjectionMatrix *= ViewPort;
	}

	// �θ� ����
	void SetParent(GameEngineTransform* _Parent);

	// �θ��� ������ �ڽĿ��� ����
	void CalChild()
	{
		for (GameEngineTransform* ChildTrans : Child)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}

protected:

private:
	// ��� ���� �ǽõǸ� ������ ��� �����Ͱ� �ֽ�ȭ��
	void TransformUpdate();

	// ���� ũ��(��)��
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	Quaternion LocalQuaternion = DirectX::XMQuaternionIdentity(); // XMQuaternionIdentity() = �׵����ʹϿ� ����
	float4 LocalPosition = float4::Zero;

	// ���� ũ��(��)��
	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	Quaternion WorldQuaternion = DirectX::XMQuaternionIdentity();
	float4 WorldPosition = float4::Zero;

	float4x4 LocalScaleMatrix;               // ���� ũ�� ���
	float4x4 LocalRotationMatrix;            // ���� ȸ�� ���
	float4x4 LocalPositionMatrix;            // ���� �̵� ���

	float4x4 LocalWorldMatrix;               // ���ÿ��� ���
	float4x4 WorldMatrix;                    // ���� ��� (SRT)

	float4x4 View;                           // �����
	float4x4 Projection;                     // �������� ���
	float4x4 ViewPort;                       // ����Ʈ ���
	float4x4 WorldViewProjectionMatrix;      // ����� * �����������

	GameEngineTransform* Parent = nullptr;   // weak_ptr ����
	std::list<GameEngineTransform*> Child;   // �θ��ڽİ��踦 �����Ѵ�.
};

