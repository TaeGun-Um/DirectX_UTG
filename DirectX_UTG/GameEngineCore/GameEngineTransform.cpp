#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::TransformUpdate()
{
	TransData.ScaleMatrix.Scale(TransData.Scale);

	TransData.Rotation.w = 0.0f;
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();
	TransData.PositionMatrix.Pos(TransData.Position);

	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;


	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}
	else // 차이
	{
		float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
		float4 PScale, PRotation, PPosition;
		ParentWorldMatrix.Decompose(PScale, PRotation, PPosition);


		if (true == AbsoluteScale)
		{
			// 부모쪽 행렬의 스케일을 1
			PScale = float4::One;
		}
		if (true == AbsoluteRotation)
		{
			// 부모의 회전 
			PRotation = float4::Zero;
			PRotation.EulerDegToQuaternion();
		}
		if (true == AbsolutePosition)
		{
			PPosition = float4::Zero;
		}

		float4x4 MatScale, MatRot, MatPos;

		//scale
		MatScale.Scale(PScale);

		//rot
		MatRot = PRotation.QuaternionToRotationMatrix();

		//pos
		MatPos.Pos(PPosition);

		TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
	}

	// 마지막으로 세팅된 값에서 Local, World 행렬 값 추출 후 저장
	WorldDecompose();
	LocalDecompose();
}

// 로컬 디컴포즈
void GameEngineTransform::LocalDecompose()
{
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

}

// 월드 디컴포즈
void GameEngineTransform::WorldDecompose()
{
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

}

void GameEngineTransform::AbsoluteReset()
{
	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

// 부모 설정
void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	if (IsDebug())
	{
		int a = 0;
	}

	Parent = _Parent;

	TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.WorldMatrix.InverseReturn();

	LocalDecompose();

	TransData.Position = TransData.LocalPosition;
	TransData.Rotation = TransData.LocalRotation;
	TransData.Scale = TransData.LocalScale;

	TransformUpdate();
	AbsoluteReset();

	Parent->Child.push_back(this);
}

// 자식 계산
void GameEngineTransform::CalChild()
{
	for (GameEngineTransform* ChildTrans : Child)
	{
		if (false == ChildTrans->AbsoluteScale)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		}

		if (false == ChildTrans->AbsoluteRotation)
		{
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		}

		if (false == ChildTrans->AbsolutePosition)
		{
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}
}

float4 GameEngineTransform::GetLocalScale()
{
	return TransData.LocalScale;
}

float4 GameEngineTransform::GetLocalRotation()
{
	return TransData.LocalRotation;
}

float4 GameEngineTransform::GetLocalPosition()
{
	return TransData.LocalPosition;
}

float4 GameEngineTransform::GetWorldScale()
{
	return TransData.WorldScale;
}

float4 GameEngineTransform::GetWorldRotation()
{
	return TransData.WorldRotation;
}

float4 GameEngineTransform::GetWorldPosition()
{
	return TransData.WorldPosition;
}


