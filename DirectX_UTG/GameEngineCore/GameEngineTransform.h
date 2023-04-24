#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// �ϴ�, ����ī�޶��� �� �̷� ����ü�� �����ϰ� ���� ������ �� �ҷ����� ������ ���� ���ϴ�
struct TransformData
{
	// ���� ũ��(��)��
	float4 LocalScale;
	float4 LocalRotation;
	Quaternion LocalQuaternion; // XMQuaternionIdentity() = �׵����ʹϿ� ����
	float4 LocalPosition;

	// ���� ũ��(��)��
	float4 WorldScale;
	float4 WorldRotation;
	Quaternion WorldQuaternion;
	float4 WorldPosition;

	float4x4 LocalScaleMatrix;               // ���� ũ�� ���
	float4x4 LocalRotationMatrix;            // ���� ȸ�� ���
	float4x4 LocalPositionMatrix;            // ���� �̵� ���

	float4x4 LocalWorldMatrix;               // ���ÿ��� ���
	float4x4 WorldMatrix;                    // ���� ���

	float4x4 View;                           // �����
	float4x4 Projection;                     // �������� ���
	float4x4 ViewPort;                       // ����Ʈ ���
	float4x4 WorldViewProjectionMatrix;      // ����� * �����������
	
public:
	// ����ϰ� ���� ������ �� �ֱ� ������ �ʱ�ȭ�� �����ڿ��� �ǽ�
	TransformData()
	{
		LocalScale = float4::One;
		LocalRotation = float4::Null;
		LocalQuaternion = float4::Null;
		LocalPosition = float4::Zero;
		WorldScale = float4::One;
		WorldRotation = float4::Null;
		WorldQuaternion = float4::Null;
		WorldPosition = float4::Zero;
	}
};

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
		TransData.WorldScale = _Value;

		if (nullptr == Parent)
		{
			TransData.LocalScale = TransData.WorldScale;
		}
		else
		{
			TransData.LocalScale = TransData.WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
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

		TransData.WorldRotation = _Value;

		if (nullptr == Parent)
		{
			TransData.LocalRotation = TransData.WorldRotation;
		}
		else
		{
			float4 Rot = Parent->GetWorldRotation();
			TransData.LocalRotation = TransData.WorldRotation - Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetWorldPosition(const float4& _Value)
	{
		TransData.WorldPosition = _Value;

		if (nullptr == Parent)
		{
			TransData.LocalPosition = TransData.WorldPosition;
		}
		else
		{
			TransData.LocalPosition = TransData.WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ũ�� ��� ����
	float4 GetWorldScale()
	{
		return TransData.WorldScale;
	}

	// ���� ȸ�� ��� ����
	float4 GetWorldRotation()
	{
		return TransData.WorldRotation;
	}

	// ���� �̵� ��� ����
	float4 GetWorldPosition()
	{
		return TransData.WorldPosition;
	}

	// ���� ũ�� ����
	void SetLocalScale(const float4& _Value)
	{
		TransData.LocalScale = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldScale = TransData.LocalScale;
		}
		else
		{
			TransData.WorldScale = TransData.LocalScale * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ȸ�� ����
	void SetLocalRotation(const float4& _Value)
	{
		TransData.LocalRotation = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldRotation = TransData.LocalRotation;
		}
		else
		{
			TransData.WorldRotation = TransData.LocalRotation + Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetLocalPosition(const float4& _Value)
	{
		TransData.LocalPosition = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldPosition = TransData.LocalPosition;
		}
		else
		{
			TransData.WorldPosition = TransData.LocalPosition * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	// ���� ũ�� ��� ����
	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}

	// ���� ȸ�� ��� ����
	float4 GetLocalRotation()
	{
		return TransData.LocalRotation;
	}

	// ���� �̵� ��� ����
	float4 GetLocalPosition()
	{
		return TransData.LocalPosition;
	}

	// ���� ��� ����
	const float4x4 GetWorldMatrix()
	{
		return TransData.WorldMatrix;
	}

	// ���� ��� ����(���۷���)
	const float4x4& GetWorldMatrixRef()
	{
		return TransData.WorldMatrix;
	}

	// ���ÿ��� ��� ����
	float4x4 GetLocalWorldMatrix()
	{
		return TransData.LocalWorldMatrix;
	}

	// ���ÿ��� ��� ����(���۷���)
	const float4x4& GetLocalWorldMatrixRef()
	{
		return TransData.LocalWorldMatrix;
	}

	// ���� ũ�� Add
	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.LocalScale + _Value);
	}

	// ���� ȸ�� Add
	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.LocalRotation + _Value);
	}

	// ���� �̵� Add
	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.LocalPosition + _Value);
	}

	// ���� ũ�� Add
	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.WorldScale + _Value);
	}

	// ���� ȸ�� Add
	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.WorldRotation + _Value);
	}

	// ���� �̵� Add
	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.WorldPosition + _Value);
	}

	// ���忡�� �ڽ��� �ٶ󺸴� ���� ������������ ����
	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// ���忡�� �ڽ��� �� ���� ������������ ����
	float4 GetWorldBackVector()
	{
		return -GetWorldForwardVector();
	}

	// ���忡�� �ڽ��� ���� ���ϴ� ������������ ����
	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// ���忡�� �ڽ��� �Ʒ��η� ���ϴ� ������������ ����
	float4 GetWorldDownVector()
	{
		return -GetWorldUpVector();
	}

	// ���忡�� �ڽ��� ������ ���� ������������ ����
	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// ���忡�� �ڽ��� ���� ���� ������������ ����
	float4 GetWorldLeftVector()
	{
		return -GetWorldRightVector();
	}

	// ���ÿ��� �ڽ��� �ٶ󺸴� ���� ���� ������������ ����
	float4 GetLocalForwardVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// ���ÿ��� �ڽ��� ���� ���ϴ� ���� ������������ ����
	float4 GetLocalUpVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// ���ÿ��� �ڽ��� ������ ���� ������������ ����
	float4 GetLocalRightVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// ���� �������� ��� ����
	const float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	// ���� �������� ��� ����(���۷���)
	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	// ī�޶� ���(��, ��������) ����
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	// ī�޶� ���(����Ʈ) ����
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		TransData.ViewPort = _ViewPort;
		TransData.WorldViewProjectionMatrix *= TransData.ViewPort;
	}

	// Transform �����͸� ���۷����� ����
	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	// Transform ������ ����
	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
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

	// �������� -�� �����ϸ� �¿찡 �����ȴ�.
	void SetLocalFlipScaleX()
	{
		TransData.LocalScale.x = -TransData.LocalScale.x;
		SetLocalScale(TransData.LocalScale);
	}

	// �������� �ø�
	void SetLocalNegativeScaleX()
	{
		if (0 < TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

	// ���������� �ø�
	void SetLocalPositiveScaleX()
	{
		if (0 > TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

protected:

private:
	// ��� ���� �ǽõǸ� ������ ��� �����Ͱ� �ֽ�ȭ��
	void TransformUpdate();

	TransformData TransData;

	GameEngineTransform* Parent = nullptr;   // weak_ptr ����
	std::list<GameEngineTransform*> Child;   // �θ��ڽİ��踦 �����Ѵ�.
};

