#pragma once
#include "GameEngineResource.h"

// 설명 : 랜더링 파이프라인 단계에서 Resterizer 단계를 담당하는 클래스
class GameEngineRasterizer : public GameEngineResource<GameEngineRasterizer>
{
public:
	// constrcuter destructer
	GameEngineRasterizer();
	~GameEngineRasterizer();

	// delete Function
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;

	// 래스터라이저를 Create한 뒤 리소스에 푸쉬백
	static std::shared_ptr<GameEngineRasterizer> Create(const std::string_view& _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineRasterizer> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

	// ResCreate()에서 두개 다 만들었지만, 기본은 일단 솔리드로 설정. 나중에 바꾸고싶으면 호출하면 된다.
	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		switch (_Value)
		{
		case D3D11_FILL_WIREFRAME:
			CurState = WireframeState;
			break;
		case D3D11_FILL_SOLID:
			CurState = SolidState;
			break;
		default:
			break;
		}
	}

	// 레스터라이저의 CULL을 정하는 것. Cull이 변경되면 다시 만드는 인터페이스(ResCreate(Desc))
	inline void SetCULL_MODE(D3D11_CULL_MODE _Value)
	{
		Desc.CullMode = _Value;
		ResCreate(Desc);
	}

protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Value);

private:
	D3D11_RASTERIZER_DESC Desc = {};                  // 레스터리아저 요청값을 저장할 DESC 변수
	ID3D11RasterizerState* CurState = nullptr;        // 고정기능 단계는 보통 State를 넘겨달라고 요청한다. 현재의 State
	ID3D11RasterizerState* SolidState = nullptr;      // FILL의 솔리드 State, 두 개 선언한 이유는 둘 다 만들 것이기 때문
	ID3D11RasterizerState* WireframeState = nullptr;  // FILL의 와이어프레임 State, 두 개 선언한 이유는 둘 다 만들 것이기 때문

	void Release();

};

