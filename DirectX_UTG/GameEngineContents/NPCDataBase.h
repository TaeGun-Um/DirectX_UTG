#pragma once

enum class NPC
{
	AppleTraveller,
	Axeman,
	Canteen,
	Coin,
	FishGirl,
	Unknown
};

// Ό³Έν :
class NPCDataBase : public GameEngineActor
{
public:
	// constrcuter destructer
	NPCDataBase();
	~NPCDataBase();

	// delete Function
	NPCDataBase(const NPCDataBase& _Other) = delete;
	NPCDataBase(NPCDataBase&& _Other) noexcept = delete;
	NPCDataBase& operator=(const NPCDataBase& _Other) = delete;
	NPCDataBase& operator=(NPCDataBase&& _Other) noexcept = delete;

	void NPCSetting();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AssitantRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	NPC NPCValue = NPC::Unknown;

};

