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

	// VertexLayOut ����
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);

	// ���ؽ� ������ ����� ��ǲ ���̾ƿ��� ������ �� �߿��ϴ�.
	// ��ǲ ���̾ƿ��� ���� ��, ���� ������ �־���� �Ѵ�.
	// ����ͺ��� ���� �־��ִ°� ���������
	// ���� ������ �ٲ�ٴ���, ���� �ͺ��� �� ���� �����ϸ� �ȵȴ�.
	// ������ POSITION�� COLOR�� ��������� POSITION, COLOR�� ������� �����Ͽ� �־��ش�.

	// ���÷� ����
	// ���÷��� Vertex ���� ���� �ؾ��ؼ� ���⼭ �ε� �ǽ�
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

	// Rect ����
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		// Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		// Desc.FrontCounterClockwise = FALSE;
		// �̱� ������ �׸��� ������ �ð� �������� �ǽ�

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		// �����ؼ� �ո�� �޸��� �����߾��� ��
		// �ð�������� �ؾ� ���� ����
		
		// � ��ü�� ������� �� �� ��ü�� �޸��� �����̴�.
		// �츮 ������ �ڷ� �������� ���� ����
		// �ڽ��� ġ�� �޸��� ������� �ϴ� ���̴�.
		// ��� ���� �߿����� ����, �ٲܰ���

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
		// 230414 ��ǲ���̾ƿ� ���� ����
		// Vertex�� ArrVertex�� ���⼭ ���޵�
		// �׷��� ������ VertexBuffer�� ��ǲ���̾ƿ��� ������ ���� ��� ���� �� �ֵ��� �������̽� ����
		// GameEngineVertexBuffer::Create �ܰ迡�� Res->LayOutInfo = &VertexType::LayOut; �߰�
	}

	// ���� ����
	{
		D3D11_BLEND_DESC Desc = { 0, };

		// �ڵ����� ���ĺκ��� �����ؼ� ������ִ� �ǵ�
		// ��������ϴ�.
		Desc.AlphaToCoverageEnable = false;
		// ���带 ������ �����ų�
		// TRUE�� ���带 ������ �ֽ��ϴ�.
		// false�� ��� ����Ÿ���� �ְ� 0���� ���õ� �ɷ� ���δ� ����.
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		GameEngineBlend::Create("AlphaBlend", Desc);
	}

	// Box ����
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

	// ���̴� ������
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
	}

	// �����Ͷ������� Desc ����
	{
		D3D11_RASTERIZER_DESC Desc = {};

		// 1�� ���� : FILL��� == �ָ���� ���̾� �������� �ִ�. ���̾� �������� ���̾�� ǥ��, �ָ����� ������ ǥ���ϴ� ���̴�.
		//                       FILL���� ������ �ʾ����� ��ȯ�� ���İ��� ���� �ʱ� ������, �츮�� �ΰ� �� ���� ����� �����̴�.
		//                       ������ ���� �ܰ��̸�, ���������� �̷����� ��, �����Ҷ��� ȣ����� �ʾƼ� �������.

		// 2�� ���� : CULL��� == �ո�����, �޸�����, �������(None)���� ����. ��� �� �������ϴ� ���̴�. �׷��� SetCULL_MODE(_Value)��
		//                       ����� ȣ��� ������ ResCreate(Desc)�� �ǽ��Ͽ� �ٽ� ����� �������̽��� ������. ���� ������ Front�� �ǽ�
		//                       �̰��� ������ ������ ResCreate()�� �ٽ� ���� ������ ������ �׷� ��(�̷��� �ص� ��� ���� ������ �����ٴ� ��)

		// 3�� ���� : FrontCounterClockwise == �ﰢ���� �ո����� �޸����� ����. �� �Ű������� TRUE �̸� ���� �� ���� ��󿡼� 
		//                                     �ð� �ݴ� �����̸� �ﰢ���� ������ ���ϴ� ������ ���ֵǰ� �ð� �����̸� �ĸ��� ���ϴ� ������ ���ֵ˴ϴ�. 
		//                                     �� �Ű������� FALSE �̸� �� �ݴ��Դϴ� (������Ų�ٴ� ��).
		 
		// 4�� ���� : DepthBias == �ȼ��� ���� �� �߰�. ���� ���⿡ ���� ������ ���� ���� �� ����(msdn)
		// 5�� ���� : DepthBiasClamp == �ȼ��� �ִ� ���� ���� �߰�. ���� ���⿡ ���� ������ ���� ���� �� ����(msdn)
		// 6�� ���� : SlopeScaledDepthBias == �־��� �ȼ��� ���⿡ ���� ��Į��. ���� ���⿡ ���� ������ ���� ���� �� ����(msdn)
		// 7�� ���� : DepthClipEnable == �Ÿ��� ���� Ŭ���� �ǽ�. ���� ������ �������°� �̿ܿ� �̰� true�ϸ� z�� ¥��
		//                               �����ϴٰ� ���ڱ� �����Ǵ� ���͵��� �����ϸ� ���� ���ذ���
		// 8�� ���� : ScissorEnable == ���� �簢�� �ø�. ������â �ȿ��� �� ��Ʈ�� ���� �ڸ��ڳĴ� ��. false
		
		// 9�� ���� : MultisampleEnable == �ָ��� ����϶��� ��Ƽ����̾��, True�� ���, false
		//                                ���� ���� ��Ƽ�ٸ����(MSAA) ���� ��󿡼� �纯�� �Ǵ� ���� ���� ��Ƽ�ٸ���� �˰����� ������� ���θ� �����մϴ�. 
		//                                �纯�� ���� ��Ƽ �ٸ���� �˰����� ����Ϸ��� TRUE �� ���� �ϰ� ���� ���� ��Ƽ �ٸ���� �˰����� ����Ϸ��� 
		//                                FALSE �� �����մϴ�.
		
		// 10�� ���� : AntialiasedLineEnable == ���̾� ������ ����϶��� ��Ƽ����̾��, True�� ���, false
	    //                                     �� ��Ƽ�ٸ������ Ȱ��ȭ���� ���θ� �����մϴ�. �� �׸��⸦ �����ϰ� MultisampleEnable�� FALSE �� ��쿡�� ����˴ϴ�.
        //                                     ���̾� �������� ������ ǥ���ϴ� �̴ϴ�. 

		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME; // 1�� (���⼭ �����ص� ���ο��� solid�� �����)
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;      // 2��
		Desc.FrontCounterClockwise = FALSE;                    // 3��

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Desc);
	}

	// �ؽ��� ���������������� ����
	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlend("AlphaBlend");
		}
	}
}

// �����δ� �˾Ƽ� Release ������, ���� ��������� Ȯ���ϱ� ���Ͽ� ȣ���ϴ� �͵�
void GameEngineCore::CoreResourcesEnd()
{
	GameEngineMesh::ResourcesClear();
	GameEngineBlend::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
	GameEngineConstantBuffer::ResourcesClear();
	GameEngineRenderingPipeLine::ResourcesClear();
}