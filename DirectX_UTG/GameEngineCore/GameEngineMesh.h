#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

// 설명 : 3D 물체를 메쉬(mesh)라고 합니다.
class GameEngineMesh : public GameEngineResource
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
	// 소프트웨어 랜더링
	std::vector<float4> Vertexs;

};

