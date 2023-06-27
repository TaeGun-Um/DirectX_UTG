#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore/GameEngineFont.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "TransformGUI.h"
#include "OverworldGUI.h"

void CupheadCore::ContentsResourcesLoad()
{
	GameEngineFont::Load("�޸յձ�������");
	GameEngineFont::Load("Cuphead Felix");

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

	if (nullptr == GameEngineTexture::Find("EnterMessage.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");

		GameEngineTexture::Load(NewDir.GetPlusFileName("EnterMessage.png").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Enter"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Camera");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Enter").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Exit").GetFullPath());
	}
}

void CupheadCore::ContentsKeyBind()
{
	if (false == GameEngineInput::IsKey("MoveUp"))
	{
		GameEngineInput::CreateKey("MoveUp", VK_UP);
		GameEngineInput::CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("Attack", 'Z');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("Hold", 'C');
		GameEngineInput::CreateKey("EX", 'V');
		GameEngineInput::CreateKey("Test", 'Q');
		GameEngineInput::CreateKey("Dash", VK_SHIFT);
		GameEngineInput::CreateKey("WeaponSwap", VK_TAB);
		GameEngineInput::CreateKey("HPMax", VK_F1);
		GameEngineInput::CreateKey("EXMax", VK_F2);
		GameEngineInput::CreateKey("SpeedUp", VK_F3);
	}

	if (false == GameEngineInput::IsKey("FadeIn"))
	{
		GameEngineInput::CreateKey("FadeIn", '1');
		GameEngineInput::CreateKey("FadeOut", '2');

		GameEngineInput::CreateKey("NextLevel", 'L');
		GameEngineInput::CreateKey("PrevLevel", 'K');
	}
}

void CupheadCore::ContentsResourcesCreate()
{
	{
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		// �ؽ�ó�� �ָ������� ��������
		// �ȹ�����.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::ReSetting("ENGINEBASE", SamperData);
	}

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

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	//{
	//	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("DebugRect");
	//	//Pipe->SetVertexBuffer("Rect");
	//	//Pipe->SetIndexBuffer("Rect");
	//	Pipe->SetVertexShader("DebugMeshRender.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("DebugMeshRender.hlsl");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("HBSCSprite");

		Pipe->SetVertexShader("HBSCShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("HBSCShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	// IMGUI Create
	GameEngineGUI::GUIWindowCreate<TransformGUI>("TransformGUI");
	GameEngineGUI::GUIWindowCreate<OverworldGUI>("OverworldGUI");
}