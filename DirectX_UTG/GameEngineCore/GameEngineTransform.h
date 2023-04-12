#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// 설명 : 특정한 문체의 크기 회전 이동에 관련된 기하속성을 관리해준다.
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

	// 월드 크기 지정
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

	// 월드 위치 지정
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

	// 월드 이동 지정
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

	// 월드 크기 행렬 리턴
	float4 GetWorldScale()
	{
		return WorldScale;
	}

	// 월드 회전 행렬 리턴
	float4 GetWorldRotation()
	{
		return WorldRotation;
	}

	// 월드 이동 행렬 리턴
	float4 GetWorldPosition()
	{
		return WorldPosition;
	}

	// 로컬 크기 지정
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

	// 로컬 회전 지정
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

	// 로컬 이동 지정
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

	// 로컬 크기 행렬 리턴
	float4 GetLocalScale()
	{
		return LocalScale;
	}

	// 로컬 회전 행렬 리턴
	float4 GetLocalRotation()
	{
		return LocalRotation;
	}

	// 로컬 이동 행렬 리턴
	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	// 월드 행렬 리턴
	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	// 월드 행렬 리턴(래퍼런스)
	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	// 로컬월드 행렬 리턴
	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	// 로컬월드 행렬 리턴(래퍼런스)
	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	// 로컬 크기 Add
	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(LocalScale + _Value);
	}

	// 로컬 회전 Add
	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(LocalRotation + _Value);
	}

	// 로컬 이동 Add
	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(LocalPosition + _Value);
	}

	// 월드에서 자신이 바라보는 방향 월드 단위기저벡터 리턴
	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// 월드에서 자신의 위로 향하는 월드 단위기저벡터 리턴
	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// 월드에서 자신의 오른쪽 방향 단위기저벡터 리턴
	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// 로컬에서 자신이 바라보는 방향 월드 단위기저벡터 리턴
	float4 GetLocalForwardVector()
	{
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// 로컬에서 자신의 위로 향하는 월드 단위기저벡터 리턴
	float4 GetLocalUpVector()
	{
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// 로컬에서 자신의 오른쪽 방향 단위기저벡터 리턴
	float4 GetLocalRightVector()
	{
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// 월드 프로젝션 행렬 리턴
	const float4x4 GetWorldViewProjectionMatrix()
	{
		return WorldViewProjectionMatrix;
	}

	// 월드 프로젝션 행렬 리턴(래퍼런스)
	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return WorldViewProjectionMatrix;
	}

	// 카메라 행렬(뷰, 프로젝션) 적용
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		View = _View;
		Projection = _Projection;
		WorldViewProjectionMatrix = WorldMatrix * View * Projection;
	}

	// 카메라 행렬(뷰포트) 적용
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		ViewPort = _ViewPort;
		WorldViewProjectionMatrix *= ViewPort;
	}

	// 부모 설정
	void SetParent(GameEngineTransform* _Parent);

	// 부모의 영향을 자식에게 적용
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
	// 행렬 곱이 실시되면 무조건 행렬 데이터가 최신화됨
	void TransformUpdate();

	// 로컬 크자(쿼)이
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	Quaternion LocalQuaternion = DirectX::XMQuaternionIdentity(); // XMQuaternionIdentity() = 항등쿼터니온 생성
	float4 LocalPosition = float4::Zero;

	// 월드 크자(쿼)이
	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	Quaternion WorldQuaternion = DirectX::XMQuaternionIdentity();
	float4 WorldPosition = float4::Zero;

	float4x4 LocalScaleMatrix;               // 로컬 크기 행렬
	float4x4 LocalRotationMatrix;            // 로컬 회전 행렬
	float4x4 LocalPositionMatrix;            // 로컬 이동 행렬

	float4x4 LocalWorldMatrix;               // 로컬월드 행렬
	float4x4 WorldMatrix;                    // 월드 행렬 (SRT)

	float4x4 View;                           // 뷰행렬
	float4x4 Projection;                     // 프로젝션 행렬
	float4x4 ViewPort;                       // 뷰포트 행렬
	float4x4 WorldViewProjectionMatrix;      // 뷰행렬 * 프로젝션행렬

	GameEngineTransform* Parent = nullptr;   // weak_ptr 구조
	std::list<GameEngineTransform*> Child;   // 부모자식관계를 결정한다.
};

