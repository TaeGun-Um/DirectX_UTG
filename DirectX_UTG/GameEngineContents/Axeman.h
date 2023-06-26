#pragma once

#include "NPCDataBase.h"
#include "NPC_TextBox.h"

// Ό³Έν :
class Axeman : public NPCDataBase
{
public:
	static Axeman* AxemanPtr;

	// constrcuter destructer
	Axeman();
	~Axeman();

	// delete Function
	Axeman(const Axeman& _Other) = delete;
	Axeman(Axeman&& _Other) noexcept = delete;
	Axeman& operator=(const Axeman& _Other) = delete;
	Axeman& operator=(Axeman&& _Other) noexcept = delete;

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
		float4 PlusLocalPosition = float4{ -170, 140, -50 };
		float4 ActorLocalPosition = GetTransform()->GetLocalPosition();

		NPC_TextBoxRender->LocalPositionSetting(ActorLocalPosition + PlusLocalPosition);

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
	int TextEndCount = 2;

	bool NextStep = false;

	std::vector<std::string> NPCScript;
	void ScriptInit();
};

