#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

// 설명 : ID3DBlob를 활용하기 위한 GameEngineShader 상속
class GameEngineVertexShader : public GameEngineResource<GameEngineVertexShader>, public GameEngineShader
{
public:
	// constrcuter destructer
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete Function
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

protected:

private:

};

