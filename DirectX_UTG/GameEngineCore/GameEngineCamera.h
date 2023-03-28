#pragma once
#include "GameEngineActor.h"

// ���� : �� ����� Ȱ���ϱ� ���� ī�޶� ����, ���� ���� �� maincamera�� shared_ptr�� ��� �ϳ� �����ȴ�(GELevel�� ������ �ܰ迡�� ������).
class GameEngineCamera : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

protected:

private:

};

