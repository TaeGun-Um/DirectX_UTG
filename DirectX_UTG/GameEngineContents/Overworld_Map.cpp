#include "PrecompileHeader.h"
#include "Overworld_Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Overworld_Map::Overworld_Map() 
{
}

Overworld_Map::~Overworld_Map() 
{
}

void Overworld_Map::Start()
{
	// 리소스 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("CupHead_Resource");
		NewDir.Move("CupHead_Resource");
		NewDir.Move("Image");
		NewDir.Move("Level");
		NewDir.Move("Overworld");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (nullptr == RenderPtr)
	{
		RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
		RenderPtr->SetTexture("Overworld_Map.png");
		RenderPtr->GetTransform()->SetLocalScale({ 4000, 2300, 1 });
		RenderPtr->GetTransform()->SetLocalPosition({ 0, 0, 100 });
	}
}
void Overworld_Map::Update(float _DeltaTime)
{

}