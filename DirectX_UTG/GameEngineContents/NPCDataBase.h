#pragma once

enum class NPCValue
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


protected:
	void Start() override {}
	void Update(float _DeltaTime) override {}
	void Render(float _DeltaTime) override {}
	
	void CollisionCheck(std::shared_ptr<class GameEngineCollision> _Collision);
	void NPCLoad(NPCValue _NValue);

private:
	NPCValue NValue = NPCValue::Unknown;

};

