#pragma once

#include "NPCDataBase.h"
#include "NPC_TextBox.h"

// ���� :
class Canteen : public NPCDataBase
{
public:
	static Canteen* CanteenPtr;

	// constrcuter destructer
	Canteen();
	~Canteen();

	// delete Function
	Canteen(const Canteen& _Other) = delete;
	Canteen(Canteen&& _Other) noexcept = delete;
	Canteen& operator=(const Canteen& _Other) = delete;
	Canteen& operator=(Canteen&& _Other) noexcept = delete;

	void CollisionRenderOn()
	{
		CollisionRenderPtr->On();
	}

	void CollisionRenderOff()
	{
		CollisionRenderPtr->Off();
	}

	void TextBoxPositionSetting()
	{
		ScriptInit();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	std::shared_ptr<class NPC_TextBox> NPC_TextBoxRender = nullptr;
	std::shared_ptr<class GameEngineFontRenderer> FontRender = nullptr;

	void InitRenderSetting();
	void InitCollisionSetting();
	void TextBoxOn(float _DeltaTime);

	float BoxInterActionDelayTime = 0.0f;

	int TextCount = 0;
	int TextEndCount = 1;

	bool NextStep = false;

	std::vector<std::string> NPCScript;
	void ScriptInit();
	size_t NumberofLines();
	size_t NumberofCharacters();
	void TextBoxSetting();
	void FontPositionSetting();
};

