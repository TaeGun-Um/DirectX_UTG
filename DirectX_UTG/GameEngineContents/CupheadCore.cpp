#include "PrecompileHeader.h"
#include "CupheadCore.h"

#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "First_OpeningLevel.h"
#include "Second_OpeningLevel.h"
#include "TutorialLevel.h"
#include "WaitingRoomLevel.h"
#include "OverworldLevel.h"
#include "FrogLevel.h"
#include "DragonLevel.h"
#include "MouseLevel.h"
#include "EndingLevel.h"

#include "TransformGUI.h"

CupheadCore::CupheadCore()
{
}

CupheadCore::~CupheadCore()
{
}

void CupheadCore::GameStart()
{
	new int(); // �ŷ��� ��

	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<First_OpeningLevel>();
	GameEngineCore::CreateLevel<Second_OpeningLevel>();
	GameEngineCore::CreateLevel<WaitingRoomLevel>();
	GameEngineCore::CreateLevel<TutorialLevel>();
	GameEngineCore::CreateLevel<OverworldLevel>();
	GameEngineCore::CreateLevel<FrogLevel>();
	GameEngineCore::CreateLevel<DragonLevel>();
	GameEngineCore::CreateLevel<MouseLevel>();
	GameEngineCore::CreateLevel<EndingLevel>();

	GameEngineCore::ChangeLevel("OverworldLevel");
}

void CupheadCore::GameEnd()
{

}

void CupheadCore::ContentsResourcesCreate()
{
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