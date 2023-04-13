#pragma once
#include "GameEngineResource.h"

// 설명 : 다이렉트X의 랜더링파이프라인 과정을 담은 클래스
class GameEngineRenderingPipeLine : public GameEngineResource<GameEngineRenderingPipeLine>
{
public:
	// constrcuter destructer
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	// 각 단계 클래스에서 Load를 마친 값들에 대해 Set 함수 실시
	void SetVertexBuffer(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);

	void Render();

protected:

private:
	// DirectX RenderingPipeLine 과정
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	void HullShader();
	void Tessellator();
	void DomainShader();
	void GeometryShaeder();
	void Rasterizer();
	void PixelShader();
	void OutputMerger();


	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;

};

