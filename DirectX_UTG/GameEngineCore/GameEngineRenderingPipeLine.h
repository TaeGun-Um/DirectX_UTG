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

	// DirectX RenderingPipeLine 과정
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();

	// void HullShader(); 버텍스를 쪼개기 위한 표시를 새기고
	// void Tessellator(); 쪼갠다.
	// void DomainShader(); 입자처리
	// void GeometryShaeder(); 버텍스 생성.

	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	void SetVertexBuffer(const std::string_view& _Value);

protected:

private:
	std::shared_ptr<class GameEngineVertexBuffer> VertexBuffer;

};

