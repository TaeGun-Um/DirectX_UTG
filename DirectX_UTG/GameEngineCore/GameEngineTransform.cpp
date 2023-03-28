#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}

// ��� ��Ŀ� ���� �����, LocalWorldMatrix�� ����ȴ�.
void GameEngineTransform::TransformUpdate()
{
	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;
}