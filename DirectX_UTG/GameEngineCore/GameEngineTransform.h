#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// 일단, 프리카메라모드 시 이런 구조체를 선언하고 값을 저장한 뒤 불러오는 형식을 쓰면 편하다
struct TransformData
{
	// 로컬 크자(쿼)이
	float4 LocalScale;
	float4 LocalRotation;
	Quaternion LocalQuaternion; // XMQuaternionIdentity() = 항등쿼터니온 생성
	float4 LocalPosition;

	// 월드 크자(쿼)이
	float4 WorldScale;
	float4 WorldRotation;
	Quaternion WorldQuaternion;
	float4 WorldPosition;

	float4x4 LocalScaleMatrix;               // 로컬 크기 행렬
	float4x4 LocalRotationMatrix;            // 로컬 회전 행렬
	float4x4 LocalPositionMatrix;            // 로컬 이동 행렬

	float4x4 LocalWorldMatrix;               // 로컬월드 행렬
	float4x4 WorldMatrix;                    // 월드 행렬

	float4x4 View;                           // 뷰행렬
	float4x4 Projection;                     // 프로젝션 행렬
	float4x4 ViewPort;                       // 뷰포트 행렬
	float4x4 WorldViewProjectionMatrix;      // 뷰행렬 * 프로젝션행렬
	
public:
	// 빈번하게 값을 변경할 수 있기 때문에 초기화는 생성자에서 실시
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

	// 월드 위치 지정
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

	// 월드 이동 지정
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

	// 월드 크기 행렬 리턴
	float4 GetWorldScale()
	{
		return TransData.WorldScale;
	}

	// 월드 회전 행렬 리턴
	float4 GetWorldRotation()
	{
		return TransData.WorldRotation;
	}

	// 월드 이동 행렬 리턴
	float4 GetWorldPosition()
	{
		return TransData.WorldPosition;
	}

	// 로컬 크기 지정
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

	// 로컬 회전 지정
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

	// 로컬 이동 지정
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

	// 로컬 크기 행렬 리턴
	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}

	// 로컬 회전 행렬 리턴
	float4 GetLocalRotation()
	{
		return TransData.LocalRotation;
	}

	// 로컬 이동 행렬 리턴
	float4 GetLocalPosition()
	{
		return TransData.LocalPosition;
	}

	// 월드 행렬 리턴
	const float4x4 GetWorldMatrix()
	{
		return TransData.WorldMatrix;
	}

	// 월드 행렬 리턴(래퍼런스)
	const float4x4& GetWorldMatrixRef()
	{
		return TransData.WorldMatrix;
	}

	// 로컬월드 행렬 리턴
	float4x4 GetLocalWorldMatrix()
	{
		return TransData.LocalWorldMatrix;
	}

	// 로컬월드 행렬 리턴(래퍼런스)
	const float4x4& GetLocalWorldMatrixRef()
	{
		return TransData.LocalWorldMatrix;
	}

	// 로컬 크기 Add
	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.LocalScale + _Value);
	}

	// 로컬 회전 Add
	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.LocalRotation + _Value);
	}

	// 로컬 이동 Add
	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.LocalPosition + _Value);
	}

	// 월드 크기 Add
	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.WorldScale + _Value);
	}

	// 월드 회전 Add
	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.WorldRotation + _Value);
	}

	// 월드 이동 Add
	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.WorldPosition + _Value);
	}

	// 월드에서 자신이 바라보는 방향 단위기저벡터 리턴
	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// 월드에서 자신의 뒤 방향 단위기저벡터 리턴
	float4 GetWorldBackVector()
	{
		return -GetWorldForwardVector();
	}

	// 월드에서 자신의 위로 향하는 단위기저벡터 리턴
	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// 월드에서 자신의 아래로로 향하는 단위기저벡터 리턴
	float4 GetWorldDownVector()
	{
		return -GetWorldUpVector();
	}

	// 월드에서 자신의 오른쪽 방향 단위기저벡터 리턴
	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// 월드에서 자신의 왼쪽 방향 단위기저벡터 리턴
	float4 GetWorldLeftVector()
	{
		return -GetWorldRightVector();
	}

	// 로컬에서 자신이 바라보는 방향 월드 단위기저벡터 리턴
	float4 GetLocalForwardVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	// 로컬에서 자신의 위로 향하는 월드 단위기저벡터 리턴
	float4 GetLocalUpVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	// 로컬에서 자신의 오른쪽 방향 단위기저벡터 리턴
	float4 GetLocalRightVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	// 월드 프로젝션 행렬 리턴
	const float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	// 월드 프로젝션 행렬 리턴(래퍼런스)
	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	// 카메라 행렬(뷰, 프로젝션) 적용
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	// 카메라 행렬(뷰포트) 적용
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		TransData.ViewPort = _ViewPort;
		TransData.WorldViewProjectionMatrix *= TransData.ViewPort;
	}

	// Transform 데이터를 레퍼런스로 리턴
	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	// Transform 데이터 세팅
	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
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

	// 스케일을 -로 변경하면 좌우가 반전된다.
	void SetLocalFlipScaleX()
	{
		TransData.LocalScale.x = -TransData.LocalScale.x;
		SetLocalScale(TransData.LocalScale);
	}

	// 왼쪽으로 플립
	void SetLocalNegativeScaleX()
	{
		if (0 < TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

	// 오른쪽으로 플립
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
	// 행렬 곱이 실시되면 무조건 행렬 데이터가 최신화됨
	void TransformUpdate();

	TransformData TransData;

	GameEngineTransform* Parent = nullptr;   // weak_ptr 구조
	std::list<GameEngineTransform*> Child;   // 부모자식관계를 결정한다.
};

