#pragma once

#include "NPCDataBase.h"
#include "NPC_TextBox.h"

enum class CoinState
{
	Idle,
	LeftTurn,
	LeftIdle_EyeLeft,
	TurnIdle_L,
	LeftIdle_EyeTurn,
	LeftIdle_EyeRight,
	RightTurn,
	RightTurn_EyeRight,
	RightTurn_EyeTurn,
	RightTurn_EyeLeft,
	TurnIdle,
};


// Ό³Έν :
class Coin : public NPCDataBase
{
public:
	static Coin* CoinPtr;

	// constrcuter destructer
	Coin();
	~Coin();

	// delete Function
	Coin(const Coin& _Other) = delete;
	Coin(Coin&& _Other) noexcept = delete;
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

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

	float AccTime = 0.0f;
	float BoxInterActionDelayTime = 0.0f;

	int TextCount = 0;
	int TextEndCount = 5;

	bool NextStep = false;

	std::vector<std::string> NPCScript;
	void ScriptInit();
	size_t NumberofLines();
	size_t NumberofCharacters();
	void TextBoxSetting();
	void FontPositionSetting();

	void ChangeState(CoinState _StateValue);
	void UpdateState(float _DeltaTime);
	CoinState StateValue = CoinState::Idle;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void LeftTurnStart();
	void LeftTurnUpdate(float _DeltaTime);
	void LeftTurnEnd();

	void LeftIdle_EyeLeftStart();
	void LeftIdle_EyeLeftUpdate(float _DeltaTime);
	void LeftIdle_EyeLeftEnd();

	void TurnIdle_LStart();
	void TurnIdle_LUpdate(float _DeltaTime);
	void TurnIdle_LEnd();

	void LeftIdle_EyeTurnStart();
	void LeftIdle_EyeTurnUpdate(float _DeltaTime);
	void LeftIdle_EyeTurnEnd();

	void LeftIdle_EyeRightStart();
	void LeftIdle_EyeRightUpdate(float _DeltaTime);
	void LeftIdle_EyeRightEnd();

	void RightTurnStart();
	void RightTurnUpdate(float _DeltaTime);
	void RightTurnEnd();

	void RightTurn_EyeRightStart();
	void RightTurn_EyeRightUpdate(float _DeltaTime);
	void RightTurn_EyeRightEnd();

	void RightTurn_EyeTurnStart();
	void RightTurn_EyeTurnUpdate(float _DeltaTime);
	void RightTurn_EyeTurnEnd();

	void RightTurn_EyeLeftStart();
	void RightTurn_EyeLeftUpdate(float _DeltaTime);
	void RightTurn_EyeLeftEnd();

	void TurnIdleStart();
	void TurnIdleUpdate(float _DeltaTime);
	void TurnIdleEnd();
};

