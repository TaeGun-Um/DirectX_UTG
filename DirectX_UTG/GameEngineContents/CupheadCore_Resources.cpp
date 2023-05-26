#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "TransformGUI.h"

void CupheadCore::ContentsResourcesCreate()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("ContentsShader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Fade");

		Pipe->SetVertexBuffer("FullRect");
		Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	if (nullptr == GameEngineSprite::Find("BlueBox"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Character");
		NewDir.Move("CupHead");
		NewDir.Move("DebugImage");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// IMGUI Create
	GameEngineGUI::GUIWindowCreate<TransformGUI>("TransformGUI");

	// �ڱ⸸�� ���̴� ����¹�
	//  1. ���ο� ���̴��� �����.
	//	2. �翬�� �װ� ������ �ܰ迡�� ������ �Ѵ�.
	//	3. ������ ������������ �����.
	//	4. ���� �������� �����.
	//	5. start�� �����ε��Ѵ�.
	//	6. �� ������ ������������ �����Ѵ�.
	//	7. �� ��������� ��ũ�� �������ش�.

	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");
	//	NewDir.Move("ContentsShader");

	//	std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

	//	// ���̴� �ڵ�������
	//	GameEngineVertexShader::Load(Files[0].GetFullPath(), "MyShader_VS");
	//	GameEnginePixelShader::Load(Files[0].GetFullPath(), "MyShader_PS");
	//}

	//{
	//	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("My2DTexture");

	//	Pipe->SetVertexBuffer("Rect");
	//	Pipe->SetIndexBuffer("Rect");
	//	Pipe->SetVertexShader("MyShader.fx");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("MyShader.fx");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}
}