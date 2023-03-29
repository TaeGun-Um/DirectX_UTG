#pragma once
#include <list>
#include <GameEngineBase/GameEngineMath.h>

// 설명 : 특정한 물체의 크기, 이동, 회전에 관련되는 기하 속성들을 관리해주는 클래스
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

	// 모든 행렬 변환 결과는 즉시 TransformUpdate()를 호출하여 적용되도록 한다.
	// 값을 변경하면 행렬의 전체 결과가 즉시 재계산되는 구조이다.
	// 결과값을 바로 확인할 수 있어서, 굉장히 직관적이다.
	// 고정된 오브젝트 만들땐 이게 좋음
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

	float4 GetLocalForwardVector()
	{
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	float4 GetLocalScale()
	{
		return LocalScale;
	}

	float4 GetLocalRotation()
	{
		return LocalRotation;
	}

	// LocalWorldMatrix는 액터에 적용된 행렬 결과값이다.
	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	// 혹시나 모를 최적화를 위한 레퍼런스값 리턴
	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	inline const void SetView(const float4x4& _View)
	{
		View = _View;
		WorldMatrix = WorldMatrix * View;
	}

protected:

private:
	void TransformUpdate();

	// weak_ptr 구조, 후에 쓸 예정
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	float4 LocalScale = float4::One;      // 크기는 0이면 변환이 안되기 때문에, 원벡터를 활용한다.
	float4 LocalRotation = float4::Zero;  // 나머지는 제로벡터
	float4 LocalPosition = float4::Zero;

	float4x4 LocalScaleMatrix;            // 크기 변환 행렬
	float4x4 LocalRotationMatrix;         // 회전 변환 행렬
	float4x4 LocalPositionMatrix;         // 이동 변환 행렬

	float4x4 LocalWorldMatrix;

	float4x4 WorldMatrix;
	float4x4 View;
};

