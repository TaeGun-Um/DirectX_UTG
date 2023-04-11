#pragma once
#include "GameEngineResource.h"

// ���� : ���̷�ƮX�� ���������������� ������ ���� Ŭ����
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

	// DirectX RenderingPipeLine ����
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();

	// void HullShader(); ���ؽ��� �ɰ��� ���� ǥ�ø� �����
	// void Tessellator(); �ɰ���.
	// void DomainShader(); ����ó��
	// void GeometryShaeder(); ���ؽ� ����.

	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	void SetVertexBuffer(const std::string_view& _Value);

protected:

private:
	std::shared_ptr<class GameEngineVertexBuffer> VertexBuffer;

};

