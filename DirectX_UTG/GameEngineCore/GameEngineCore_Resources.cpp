#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"
#include "GameEngineShaderResHelper.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineBlend.h"
#include "GameEngineTexture.h"
#include "GameEngineDepthState.h"
#include "GameEngineRasterizer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexShader.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRenderingPipeLine.h"

void GameEngineCore::CoreResourcesInit()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// VertexLayOut 생성
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);

	// 버텍스 버퍼의 내용과 인풋 레이아웃의 내용이 더 중요하다.
	// 인풋 레이아웃을 만들 때, 만든 내용은 넣어줘야 한다.
	// 만든것보다 적게 넣어주는건 상관없지만
	// 만든 순서가 바뀐다던지, 만든 것보다 더 많이 선언하면 안된다.
	// 지금은 POSITION과 COLOR를 만들었으니 POSITION, COLOR를 순서대로 선언하여 넣어준다.

	// 샘플러 생성
	// 샘플러는 Vertex 생성 전에 해야해서 여기서 로드 실시
	{
		D3D11_SAMPLER_DESC SamperData = {};

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("CLAMPSAMPLER", SamperData);
	}
	{
		D3D11_SAMPLER_DESC SamperData = {};

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAPSAMPLER", SamperData);
	}

	// Rect 생성
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		// Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		// Desc.FrontCounterClockwise = FALSE;
		// 이기 때문에 그리는 순서는 시계 방향으로 실시

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		// 외적해서 앞면과 뒷면을 구분했었던 것
		// 시계방향으로 해야 눈에 보임
		
		// 어떤 물체를 만들었을 때 그 물체는 뒷면인 상태이다.
		// 우리 엔진은 뒤로 물러나서 보고 있음
		// 박스로 치면 뒷면을 만드려고 하는 것이다.
		// 사실 별로 중요하진 않음, 바꿀거임

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
		// 230414 인풋레이아웃 생성 수업
		// Vertex는 ArrVertex로 여기서 전달됨
		// 그렇기 때문에 VertexBuffer가 인풋레이아웃의 정보를 생성 즉시 가질 수 있도록 인터페이스 구성
		// GameEngineVertexBuffer::Create 단계에서 Res->LayOutInfo = &VertexType::LayOut; 추가
	}

	// FullRect 생성
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);

		ArrVertex[0] = { { -1.0f, 1.0f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 1.0f, 1.0f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 1.0f, -1.0f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -1.0f, -1.0f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("FullRect", ArrVertex);
		GameEngineIndexBuffer::Create("FullRect", ArrIndex);
	}

	// 블랜드 세팅
	{
		D3D11_BLEND_DESC Desc = { 0, };

		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;           // ADD <-> MAX
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;  // SRC_ALPHA <-> ONE

		// 1번 인자 : 자동으로 알파 부분을 제거해서 출력해주는 것이다. 사용 시 연산이 굉장히 느려서 사용 안함. False
		// 2번 인자 : 블랜드를 여러 개 넣을 것인지 정하는 것. 랜더 타겟이 여러 개일 경우, true로 하면 랜더 타겟 하나 당 블랜드를 하나씩 만들면서 넣어줄 수도 있다.
		//            false일 경우, 하나의 블랜드만 사용한다는 뜻. 이 옵션을 선택하면 설정해줘야 하는 것이 있다. (3번부터 10번까지)
		// 3번 : 2번 세팅에서 몇 번 블랜드로 할 지 정하는 것, 우리는 SV0의 블랜드를 사용할 것이다 라는 뜻
		// 4번 : ?
		// 5번 : 더할 것인지, 뺄 것인지 정하는 것. max와 min도 있다
		// 6번 : 필터를 뭐로 할 것인지 정한다. ALPHA는 알파로 한다는 뜻. 알파로 설정할 경우, 알파도 3개의 float으로 나뉜다. (1, 1, 1, A => 1, 1, 1, 1, 1, 1)
		// 7번 : 1 - 알파, 자신의 위에 존재하는 알파(덮는 알파)가 진할 경우 옆어지게 만드는 것
		// 8, 9, 10번 : 8 ~ 10번은 RGB 설정(5 ~ 7번)과 같이 한다.

		GameEngineBlend::Create("AlphaBlend", Desc);
	}

	// Depth 세팅
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };

		// 깊이버퍼는 랜더타겟에 그려지기 전, 랜더 타겟과 똑같은 크기의 텍스쳐를 하나 만든다.
		// 텍스쳐의 한 픽셀마다 0~1까지 float으로 표현된다. 기본 세팅이면 1인 상태로 생성된다.
		// 0~1의 값인 이유는 레스터라이저에서 w 나누기 시 생성되는 값을 활용하기 때문이다.
		// 이제 특정 이미지를 텍스쳐에 그리려고 할 때, 그려지는 이미지와 깊이버퍼 텍스쳐간에 값을 비교한다.
		// 우리의 엔진 구조는 값이 작을 수록(0에 가까워 질수록) 가까이에 있는 사물이다. 이것이 적용되도록 세팅할 예정
		// 만약 그려지는 이미지의 값이 0.9라면, 해당 픽셀이 존재하는 부분은 1에서 0.9로 교체된다.
		// 다음으로 그려지는 이미지의 값이 0.5인데, 만약 0.9가 입력된 부분과 겹칠 경우, 0.9는 0.5로 교체된다.
		// 이후 적용된 값에 따라 이미지가 그려진다. 이게 Depth이다.

		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;
		
		// 1번 : 깊이 버퍼를 쓸것인지 말것인지 정하는 것. WinAPI처럼 안쓰고 RenderOrder로 할 수 있지만, 3D 처럼 하길 원하니 true
		// 2번 : 새롭게 그려지는 것이 깊이 테스트를 통과하려면, 기존에 그려진 것보다 작아야하는지 커야하는지 설정. 우리는 작은것 기준으로 한다 (Less Equal)
		// 3번 : 이용해본적이 없어서 설명 x
		// 4번 : Depth는 한 픽셀에 0~1을 float으로 표현한다. 이때, 3byte만 활용해도 충분하기 때문에, 나머지 1byte는 int 자료형으로 활용한다.
		//       이럴 경우 0 ~ 255까지의 수를 넣을 수 있는데, 이 값이 바로 스탠실이다.
		//       스탠실 값을 활용할 경우 픽셀 쉐이더에서 if 스탠실 값이 230 라면~ 이런 식으로 특정 로직에 활용할 수 있다.

		GameEngineDepthState::Create("EngineDepth", Desc);
	}
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("AlwayDepth", Desc);
	}

	// Box 생성
	{
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);

		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

		ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

		ArrVertex[12] = ArrVertex[0].RotaitonYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotaitonYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotaitonYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotaitonYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotaitonXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotaitonXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotaitonXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotaitonXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotaitonXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotaitonXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotaitonXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotaitonXDegReturn(-90.0f);
	}

	// 쉐이더 컴파일
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Merge_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Merge_PS");

		GameEngineVertexShader::Load(Files[1].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[1].GetFullPath(), "Texture_PS");
	}

	// 레스터라이저의 Desc 설정
	{
		D3D11_RASTERIZER_DESC Desc = {};

		// 1번 인자 : FILL모드 == 솔리드와 와이어 프레임이 있다. 와이어 프레임은 와이어로 표현, 솔리느는 면으로 표현하는 것이다.
		//                       FILL모드는 만들지 않았으면 전환이 순식간에 되지 않기 때문에, 우리는 두개 다 만들어서 사용할 예정이다.
		//                       어차피 세팅 단계이며, 엔진에서만 이뤄지는 것, 게임할때는 호출되지 않아서 상관없다.

		// 2번 인자 : CULL모드 == 앞면인지, 뒷면인지, 상관없음(None)인지 설정. 사실 다 만들어야하는 것이다. 그래서 SetCULL_MODE(_Value)를
		//                       만들고 호출될 때마다 ResCreate(Desc)를 실시하여 다시 만드는 인터페이스로 구성함. 지금 당장은 Front로 실시
		//                       이것이 가능한 이유는 ResCreate()로 다시 만들어도 빠르기 때문에 그런 것(이렇게 해도 상관 없을 정도로 빠르다는 뜻)

		// 3번 인자 : FrontCounterClockwise == 삼각형이 앞면인지 뒷면인지 결정. 이 매개변수가 TRUE 이면 정점 이 렌더 대상에서 
		//                                     시계 반대 방향이면 삼각형이 전면을 향하는 것으로 간주되고 시계 방향이면 후면을 향하는 것으로 간주됩니다. 
		//                                     이 매개변수가 FALSE 이면 그 반대입니다 (반전시킨다는 뜻).
		 
		// 4번 인자 : DepthBias == 픽셀의 깊이 값 추가. 깊이 편향에 대한 정보는 깊이 편향 을 참조(msdn)
		// 5번 인자 : DepthBiasClamp == 픽셀의 최대 깊이 편항 추가. 깊이 편향에 대한 정보는 깊이 편향 을 참조(msdn)
		// 6번 인자 : SlopeScaledDepthBias == 주어진 픽셀의 기울기에 대한 스칼라. 깊이 편향에 대한 정보는 깊이 편향 을 참조(msdn)
		// 7번 인자 : DepthClipEnable == 거리에 따라 클리핑 실시. 왼쪽 오른쪽 삐져나온것 이외에 이걸 true하면 z도 짜름
		//                               게임하다가 갑자기 생성되는 액터들을 생각하면 뭔지 이해가능
		// 8번 인자 : ScissorEnable == 가위 사각형 컬링. 윈도우창 안에서 또 렉트를 만들어서 자르겠냐는 뜻. false
		
		// 9번 인자 : MultisampleEnable == 솔리드 방식일때의 안티얼라이어싱, True면 사용, false
		//                                다중 샘플 앤티앨리어싱(MSAA) 렌더 대상에서 사변형 또는 알파 라인 앤티앨리어싱 알고리즘을 사용할지 여부를 지정합니다. 
		//                                사변형 라인 앤티 앨리어싱 알고리즘을 사용하려면 TRUE 로 설정 하고 알파 라인 앤티 앨리어싱 알고리즘을 사용하려면 
		//                                FALSE 로 설정합니다.
		
		// 10번 인자 : AntialiasedLineEnable == 와이어 프레임 방식일때의 안티얼라이어싱, True면 사용, false
	    //                                     선 앤티앨리어싱을 활성화할지 여부를 지정합니다. 선 그리기를 수행하고 MultisampleEnable이 FALSE 인 경우에만 적용됩니다.
        //                                     와이어 프레임은 선으로 표현하는 겁니다. 

		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME; // 1번 (여기서 지정해도 내부에서 solid로 변경됨)
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;      // 2번
		Desc.FrontCounterClockwise = FALSE;                    // 3번

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Desc);
	}

	// 텍스쳐 랜더랑파이프라인 설정
	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("EngineDepth");
		}
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Merge");
			Pipe->SetVertexBuffer("FullRect");
			Pipe->SetIndexBuffer("FullRect");
			Pipe->SetVertexShader("MergeShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("MergeShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("AlwayDepth");

			GameEngineRenderTarget::RenderTargetUnitInit();
		}
	}
}

// 실제로는 알아서 Release 되지만, 내가 명시적으로 확인하기 위하여 호출하는 것들
void GameEngineCore::CoreResourcesEnd()
{
	GameEngineMesh::ResourcesClear();
	GameEngineBlend::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineDepthState::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
	GameEngineConstantBuffer::ResourcesClear();
	GameEngineRenderingPipeLine::ResourcesClear();
}