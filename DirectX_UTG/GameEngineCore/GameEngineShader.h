#pragma once

// ���� : ���۰� ID3D11Buffer�� �����ϴ� �� ó��, ���̴��� ID3DBlob�� �����Ѵ�.
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

