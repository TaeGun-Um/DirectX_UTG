#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// �ϴ�, ����ī�޶��� �� �̷� ����ü�� �����ϰ� ���� ������ �� �ҷ����� ������ ���� ���ϴ�
struct TransformData
{
	// �ܼ� ����� ���� ���
	float4 Scale;
	float4 Rotation;
	float4 Quaternion;
	float4 Position;

	// ���� ũ��(��)��
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion; // XMQuaternionIdentity() = �׵����ʹϿ� ����
	float4 LocalPosition;

	// ���� ũ��(��)��
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;

	float4x4 ScaleMatrix;                    // ���� ũ�� ���
	float4x4 RotationMatrix;                 // ���� ȸ�� ���
	float4x4 PositionMatrix;                 // ���� �̵� ���

	float4x4 LocalWorldMatrix;               // ������ ���� ���
	float4x4 WorldMatrix;                    // ���� ���

	float4x4 View;                           // �����
	float4x4 Projection;                     // �������� ���
	float4x4 ViewPort;                       // ����Ʈ ���
	float4x4 WorldViewProjectionMatrix;      // ����� * �����������
	
public:
	// ����ϰ� ���� ������ �� �ֱ� ������ �ʱ�ȭ�� �����ڿ��� �ǽ�
	TransformData()
	{
		Scale = float4::One;
		Rotation = float4::Null;
		Quaternion = float4::Null;
		Position = float4::Zero;
	}
};

// ���� : Ư���� ��ü�� ũ�� ȸ�� �̵��� ���õ� ���ϼӼ��� �������ش�.
class GameEngineTransform : public GameEngineObjectBase
{
	friend class GameEngineObject;
	friend class GameEngineLevel;

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
		AbsoluteScale = true;
		TransData.Scale = _Value;

		TransformUpdate();
		CalChild();
	}

	// ���� ��ġ ����
	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		TransData.Rotation = _Value;

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		TransData.Position = _Value;

		TransformUpdate();
		CalChild();
	}

	// ���� ũ�� ����
	void SetLocalScale(const float4& _Value)
	{
		AbsoluteScale = false;
		TransData.Scale = _Value;

		TransformUpdate();
		CalChild();
	}

	// ���� ȸ�� ����
	void SetLocalRotation(const float4& _Value)
	{
		AbsoluteRotation = false;
		TransData.Rotation = _Value;

		TransformUpdate();
		CalChild();
	}

	// ���� �̵� ����
	void SetLocalPosition(const float4& _Value)
	{
		AbsolutePosition = false;
		TransData.Position = _Value;

		TransformUpdate();
		CalChild();
	}

	float4 GetWorldScale();    // ���� ũ�� ��� ����
	float4 GetWorldRotation(); // ���� ȸ�� ��� ����
	float4 GetWorldPosition(); // ���� �̵� ��� ����
	float4 GetLocalScale();    // ���� ũ�� ��� ����
	float4 GetLocalRotation(); // ���� ȸ�� ��� ����
	float4 GetLocalPosition(); // ���� �̵� ��� ����

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
		SetLocalScale(TransData.Scale + _Value);
	}

	// ���� ȸ�� Add
	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.Rotation + _Value);
	}

	// ���� �̵� Add
	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.Position + _Value);
	}

	// ���� ũ�� Add
	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.Scale + _Value);
	}

	// ���� ȸ�� Add
	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.Rotation + _Value);
	}

	// ���� �̵� Add
	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.Position + _Value);
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

	void SetParent(GameEngineTransform* _Parent); // �θ� ����
	void CalChild();                              // �θ��� ������ �ڽĿ��� ����

	GameEngineTransform* GetParent()
	{
		return Parent;
	}

	//// �������� -�� �����ϸ� �¿찡 �����ȴ�.
	//void SetLocalFlipScaleX()
	//{
	//	TransData.LocalScale.x = -TransData.LocalScale.x;
	//	SetLocalScale(TransData.LocalScale);
	//}

	//// �������� �ø�
	//void SetLocalNegativeScaleX()
	//{
	//	if (0 < TransData.LocalScale.x)
	//	{
	//		SetLocalFlipScaleX();
	//		return;
	//	}

	//	return;
	//}

	//// ���������� �ø�
	//void SetLocalPositiveScaleX()
	//{
	//	if (0 > TransData.LocalScale.x)
	//	{
	//		SetLocalFlipScaleX();
	//		return;
	//	}

	//	return;
	//}

	void SetLocalPositiveScaleX()
	{
		TransData.Scale.x = abs(TransData.Scale.x);
		SetLocalScale(TransData.Scale);
	}

	void SetLocalNegativeScaleX()
	{
		TransData.Scale.x = -abs(TransData.Scale.x);
		SetLocalScale(TransData.Scale);
	}

protected:

private:
	// ��� ���� �ǽõǸ� ������ ��� �����Ͱ� �ֽ�ȭ��
	void TransformUpdate();
	void WorldDecompose();
	void LocalDecompose();
	void AbsoluteReset();

	TransformData TransData;

	bool AbsoluteScale = false;
	bool AbsoluteRotation = false;
	bool AbsolutePosition = false;

	GameEngineTransform* Parent = nullptr;   // weak_ptr ����
	std::list<GameEngineTransform*> Child;   // �θ��ڽİ��踦 �����Ѵ�.
	GameEngineObject* Master = nullptr;

	void AllAccTime(float _DeltaTime);
	void AllUpdate(float _DeltaTime);
	void AllRender(float _DeltaTime);
	void AllRelease();
	void ChildRelease();
	void SetMaster(GameEngineObject* _Master);

	GameEngineObject* GetMaster()
	{
		return Master;
	}

};

