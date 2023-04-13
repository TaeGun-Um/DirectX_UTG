#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineVertexShader.h"

void GameEngineCore::CoreResourcesInit()
{
	// Rect 생성
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f,0.0f }, float4::Red };
		ArrVertex[2] = { { 0.5f, -0.5f,0.0f }, float4::Red };
		ArrVertex[3] = { { -0.5f, -0.5f,0.0f }, float4::Red };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 3, 2 };

		// 외적해서 앞면과 뒷면을 구분했었던 것
		// 시계방향으로 해야 눈에 보임
		
		// 어떤 물체를 만들었을 때 그 물체는 뒷면인 상태이다.
		// 우리 엔진은 뒤로 물러나서 보고 있음
		// 박스로 치면 뒷면을 만드려고 하는 것이다.
		// 사실 별로 중요하진 않음, 바꿀거임

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
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

	// 쉐이더 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
	}

	// 텍스쳐 랜더랑파이프라인 설정
	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
		}
	}

}

// 생성순서의 역순으로 Release
void GameEngineCore::CoreResourcesEnd()
{
	GameEngineResource<GameEngineVertexShader>::ResourcesClear();
	GameEngineResource<GameEngineVertexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
	GameEngineResource<GameEngineRenderTarget>::ResourcesClear();
}