#pragma once

#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// 설명 :
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// 모든 랜더는 DirectX 파이프라인 과정을 거친 후 출력된다.
	// 여기서 중요한건, 쉐이더가 알고 있는 것은 몇 번 슬롯에 세팅해야 한다는 것 뿐이다. 텍스쳐를 로드한다고 자동으로 이뤄지진 않는다.
	// 파이프라인이 세팅되어 있고, 어떤 쉐이더가 세팅되어 있고, 그 쉐이더는 어떤 텍스쳐를 사용했고, 어떤 샘플러 어떤 상수 버퍼를 사용했는지를 알아야 한다.
	// 우리 엔진의 인터페이스는 쉐이더를 컴파일 하고 나서 ShaderResCheck() 함수를 통해 Reflection을 이용하는 것
	// GameEngineVertexShader에서 ShaderLoad() 실행 마지막에 ShaderResCheck()를 실시함
	void SetPipeLine(const std::string_view& _Name);

	inline GameEngineShaderResHelper& GetShaderResHelper()
	{
		return ShaderResHelper;
	}

protected:
	void Render(float _Delta) override;

private:
	// 우리의 엔진 구조는 파이프와 리소스 헬퍼가 합쳐져야 랜더링되는 형식이 될 것이다.
	// "파이프 라인은 어떤 쉐이더를 써서 그릴거야"를 위함
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe; // 생성된 파이프라인을 담기 위한 shared_ptr
	GameEngineShaderResHelper ShaderResHelper;               // 텍스쳐를 위한 리소스헬퍼

};
