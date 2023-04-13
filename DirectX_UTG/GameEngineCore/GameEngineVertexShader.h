#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

// ���� : ID3DBlob�� Ȱ���ϱ� ���� GameEngineShader ���
//        ���������������� �ܰ迡�� VertexShader�� ����ϴ� Ŭ����
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

	// Shader�� ������ ������, ���� 6.0�� �������� 5.0�� ���� �����ִ�.
	// _VersionHigh�� _VersionLow�� ���� HLSL 5.0 ������ �����ϵǵ��� �����Ѵ�.
	// _EntryPoint : ���̴��� ���� �Լ� �κ��� ����. �� �Լ��� �̸��� �ٷ� EntryPoint
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = GameEnginePath(std::string(_Path.data()));

		return Load(_Path, Path.GetFileName(), _EntryPoint, _VersionHigh, _VersionLow);
	}

	// �̸�(Name) ���� Load
	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineVertexShader::Create(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	// VertexShader Setting �ܰ�, Load �� ���� ������ ShaderPtr�� Ȱ��
	void Setting() override;

protected:

private:
	// DirectX VertextShader�� ������ �����ϱ� ���� ������ ID3D11VertexShader
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

};

