#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// 쉐이더 리소스 헬퍼 클래스
class GameEngineShaderResources
{
public:
	int BindPoint = -1;                     // b0, t0 같은 몇 번째 슬롯에 세팅되어야 하는지에 대한 정보.
	std::string Name;                       // 쉐이더 이름
	class GameEngineShader* ParentShader;   // 부모 쉐이더
};

// 상수 버퍼 헬퍼 클래스
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res; // 상수 버퍼 리소스 집합
};

// 텍스쳐 세팅 헬퍼 클래스
class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;       // 텍스쳐 세팅 리소스 집합
};

// 텍스쳐나 상수 버퍼 등, 모든 리소스를 위한 헬퍼 클래스
class GameEngineShaderResHelper
{
private:
	// 상수 버퍼의 경우, 이름은 하나지만 Vertex에 사용되기도 하고 Shader에 사용되기도 한다. 이를 위한 multimap == key(first)의 중복이 가능한 map
	// 상수 버퍼는 쉐이더가 컴파일 되면서 이런 컴파일을 쓰는구나 하는 정보를 얻었을 때 상수 버퍼가 만들어진다(GameEngineShader::ShaderResCheck()로 이동)
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	// 생성된 상수 버퍼를 ConstantBuffer에 저장한다.
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	// ConstantBuffer를 순회하며 필요로 하는 GameEngineShaderResHelper를 복사
	void Copy(const GameEngineShaderResHelper& _ResHelper);
};
