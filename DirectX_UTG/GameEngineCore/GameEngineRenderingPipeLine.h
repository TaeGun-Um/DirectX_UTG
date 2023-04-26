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

	inline  std::shared_ptr<class GameEngineVertexShader> GetVertexShader()
	{
		return VertexShaderPtr;
	}

	inline  std::shared_ptr<class GameEnginePixelShader> GetPixelShader()
	{
		return PixelShaderPtr;
	}

	// 각 단계 클래스에서 Load를 마친 값들에 대해 Set 함수 실시
	void SetVertexBuffer(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);
	void SetBlendState(const std::string_view& _Value);
	void SetDepthState(const std::string_view& _Value);

	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		FILL_MODE = _Value;
	}

	// Render에서 두 함수 호출
	void RenderingPipeLineSetting();
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

	// DirectX11 랜더링 파이프라인은 고정기능 단계와 프로그래밍 가능 단계가 존재한다.
	// 고정기능 단계 == 이미 세팅은 되어있고 옵션만 이거로 하라고 하며 넘겨주고 만드는 단계 // 쉐이더 이외의 단계들
	// 프로그래밍 가능 단계 == 특정 규칙만 지키면 마음대로 설계할 수 있는 단계 // 쉐이더가 프로그래밍 가능 단계

	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;                                        // 레스터라이저의 FILL을 선택, 솔리드와 와이어프레임이 있다. 기본은 솔리드로 실시
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;  // TOPOLOGY 오류를 위한 TRIANGLELIST 기본값

	std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthState> DepthStatePtr;

};

