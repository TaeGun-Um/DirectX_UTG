#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

// 설명 : ID3DBlob를 활용하기 위한 GameEngineShader 상속
//        랜더링파이프라인 단계에서 VertexShader를 담당하는 클래스
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

	// Shader도 버전이 있으며, 현재 6.0이 나왔지만 5.0을 많이 쓰고있다.
	// _VersionHigh와 _VersionLow를 통해 HLSL 5.0 버전이 컴파일되도록 설정한다.
	// _EntryPoint : 쉐이더를 보면 함수 부분이 있음. 그 함수의 이름이 바로 EntryPoint
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));

		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	// 이름(Name) 지정 Load
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineVertexShader::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	// VertexShader Setting 단계, Load 후 값을 저장한 ShaderPtr을 활용
	void Setting() override;

protected:

private:
	// DirectX VertextShader의 정보를 참조하기 위한 포인터 ID3D11VertexShader
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

};

