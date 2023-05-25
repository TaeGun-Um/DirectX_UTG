#include "PrecompileHeader.h"
#include "Overworld_Upper.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Overworld_Upper::Overworld_Upper() 
{
}

Overworld_Upper::~Overworld_Upper() 
{
}

void Overworld_Upper::Start()
{
	if (nullptr == GameEngineTexture::Find("Overworld_Bush_Left.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Left.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\Bush\\Overworld_Bush_Right.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Mausoleum_Bush.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Boat.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Dock&Boat\\Dock.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\Lighthouse&Bouy\\Lighthouse_Buoy.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Tree_Island.png").GetFullPath());

		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\0.Small_Island\\MainBridge\\MainBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ClipBridge\\ClipBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Bridges\\ForestBridge\\ForestBridge_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Bridge\\PlaneBridge\\PlaneBridge_FrontTopper.png").GetFullPath());


		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\BotanicStair\\BotanicStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\RuseStair\\RuseStair_Topper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\1.Left\\Stairs\\TreetopStair\\TreetopStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Stairs\\HouseStair\\HouseStair_FrontTopper.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("\\Upper\\2.Right\\Stairs\\ZeppelinStair\\ZeppelinStair_Topper.png").GetFullPath());
	}

	if (nullptr == Overworld_Bush_LeftRenderPtr) // 왼쪽 섬 수풀들
	{
		Overworld_Bush_LeftRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		Overworld_Bush_LeftRenderPtr->SetScaleToTexture("Overworld_Bush_Left.png");
		Overworld_Bush_LeftRenderPtr->GetTransform()->SetLocalPosition({ -600, 0, -5 });
		Overworld_Bush_LeftRenderPtr->CameraCullingOn();
	}
	if (nullptr == Overworld_Bush_RightRenderPtr) // 오른쪽 섬 수풀들
	{
		//Overworld_Bush_RightRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//Overworld_Bush_RightRenderPtr->SetScaleToTexture("Mausoleum_Bush.png");
		//Overworld_Bush_RightRenderPtr->CameraCullingOn();
	}
	if (nullptr == Mausoleum_BushRenderPtr) // 박물관 위치 수풀
	{
		//Mausoleum_BushRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		//Mausoleum_BushRenderPtr->SetScaleToTexture("Overworld_Map.png");
		//Mausoleum_BushRenderPtr->CameraCullingOn();
	}

	if (nullptr == DockRenderPtr) // 왼쪽 섬 도크
	{
		DockRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == BoatRenderPtr) // 왼쪽 섬 배
	{
		BoatRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == LighthouseRenderPtr)	// 왼쪽 섬 등대
	{
		LighthouseRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == BuoyRenderPtr) // 왼쪽 섬 부표
	{
		BuoyRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == Tree_IslandRenderPtr) // 맵 아래 섬
	{
		Tree_IslandRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == MainBridge_FrontTopperRenderPtr) // 다리 어퍼
	{
		MainBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ClipBridge_FrontTopperRenderPtr) // 다리 어퍼
	{
		ClipBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ForestBridge_FrontTopperRenderPtr) // 다리 어퍼
	{
		ForestBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == PlaneBridge_FrontTopperRenderPtr) // 다리 어퍼
	{
		PlaneBridge_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}

	if (nullptr == BotanicStair_FrontTopperRenderPtr) // 계단 어퍼
	{
		BotanicStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == RuseStair_TopperRenderPtr) // 계단 어퍼
	{
		RuseStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == TreetopStair_FrontTopperRenderPtr) // 계단 어퍼
	{
		TreetopStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == HouseStair_FrontTopperRenderPtr) // 계단 어퍼
	{
		HouseStair_FrontTopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
	if (nullptr == ZeppelinStair_TopperRenderPtr) // 계단 어퍼
	{
		ZeppelinStair_TopperRenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	}
}
void Overworld_Upper::Update(float _DeltaTime)
{

}