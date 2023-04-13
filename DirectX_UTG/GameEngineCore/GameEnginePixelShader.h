#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

// 설명 : 랜더링파이프라인 단계에서 PixelShader 단계를 담당하는 클래스
class GameEnginePixelShader : public GameEngineResource<GameEnginePixelShader>, public GameEngineShader
{
public:
	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

	// 놀랍게도 VertexShader와 구조가 똑같다.
	// Load할 시 리소스에 푸쉬백된다.
	// 여기서의 엔트리포인트는 PS이다.
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));

		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	void Setting() override;

protected:

private:
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

};

