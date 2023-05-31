#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "TransformGUI.h"

void CupheadCore::ContentsResourcesLoad()
{
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

	if (nullptr == GameEngineSprite::Find("KNOCKOUT"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("UI");
		NewDir.Move("Font");
		NewDir.Move("Message");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("KNOCKOUT").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ready_WALLOP").GetFullPath());
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("YOU_DIED.png").GetFullPath(), 3, 7);
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

	// IMGUI Create
	GameEngineGUI::GUIWindowCreate<TransformGUI>("TransformGUI");

	// 자기만의 쉐이더 만드는법
	//  1. 새로운 쉐이더를 만든다.
	//	2. 당연히 그걸 컨텐츠 단계에서 컴파일 한다.
	//	3. 랜더링 파이프라인을 만든다.
	//	4. 나의 랜더러를 만든다.
	//	5. start를 오버로딩한다.
	//	6. 내 랜더링 파이프라인을 세팅한다.
	//	7. 각 상수버퍼의 링크를 연결해준다.

	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");
	//	NewDir.Move("ContentsShader");

	//	std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

	//	// 쉐이더 자동컴파일
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

	//{
	//	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("DebugRect");
	//	Pipe->SetVertexBuffer("Rect");
	//	Pipe->SetIndexBuffer("Rect");
	//	Pipe->SetVertexShader("CollisionDebugShader.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("CollisionDebugShader.hlsl");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}
}