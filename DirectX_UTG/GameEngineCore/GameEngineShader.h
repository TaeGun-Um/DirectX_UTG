#pragma once

#include "EngineEnum.h"
#include "GameEngineShaderResHelper.h"

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

	void CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigt = 5, UINT _VersionLow = 0);

	inline void SetEntryPoint(const std::string_view& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	// Vertex 쉐이더와 Pixel 쉐이더의 상수 버퍼 리턴
	inline const GameEngineShaderResHelper& GetShaderResHelper() const
	{
		return ResHelper;
	}

	inline ShaderType GetType()
	{
		return Type;
	}

protected:
	ID3DBlob* BinaryCode = nullptr;  // 쉐이더 코드를 2진데이터로 변형했을때 그걸 그래픽카드가 내부에 숨기고 우리에게는 BinaryCode로 준다.
	std::string Version = "";        // 쉐이더의 버전, 보통 5.0
	std::string EntryPoint = "";     // 쉐이더의 엔트리포인트
	ShaderType Type = ShaderType::None;

	// 쉐이더에서 사용한 리소스를 조사하는 함수
	void ShaderResCheck();

private:
	GameEngineShaderResHelper ResHelper; // Vertex 쉐이더와 Pixel 쉐이더상수 버퍼

};

