#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

// ���� : ���ؽ��� �̷��� ���� ���� ��, ���� ���� �Ž���� �Ѵ�.
class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

protected:

private:

};

