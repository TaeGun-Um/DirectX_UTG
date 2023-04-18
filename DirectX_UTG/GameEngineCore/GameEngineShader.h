#pragma once

#include "EngineEnum.h"
#include "GameEngineShaderResHelper.h"

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

	void CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigt = 5, UINT _VersionLow = 0);

	inline void SetEntryPoint(const std::string_view& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	// Vertex ���̴��� Pixel ���̴��� ��� ���� ����
	inline const GameEngineShaderResHelper& GetShaderResHelper() const
	{
		return ResHelper;
	}

	inline ShaderType GetType()
	{
		return Type;
	}

protected:
	ID3DBlob* BinaryCode = nullptr;  // ���̴� �ڵ带 2�������ͷ� ���������� �װ� �׷���ī�尡 ���ο� ����� �츮���Դ� BinaryCode�� �ش�.
	std::string Version = "";        // ���̴��� ����, ���� 5.0
	std::string EntryPoint = "";     // ���̴��� ��Ʈ������Ʈ
	ShaderType Type = ShaderType::None;

	// ���̴����� ����� ���ҽ��� �����ϴ� �Լ�
	void ShaderResCheck();

private:
	GameEngineShaderResHelper ResHelper; // Vertex ���̴��� Pixel ���̴���� ����

};

