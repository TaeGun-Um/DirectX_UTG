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

	// �� �ܰ� Ŭ�������� Load�� ��ģ ���鿡 ���� Set �Լ� �ǽ�
	void SetVertexBuffer(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);

	void Render();

protected:

private:
	// DirectX RenderingPipeLine ����
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

