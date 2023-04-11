#pragma once

// 설명 : 버퍼가 ID3D11Buffer를 공유하는 것 처럼, 셰이더는 ID3DBlob을 공유한다.
class GameEngineShader
{
public:
	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

protected:

private:
	ID3DBlob* BinaryCode;
	std::string Version;

};

