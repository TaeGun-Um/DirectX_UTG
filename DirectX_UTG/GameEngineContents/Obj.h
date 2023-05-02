#pragma once

// Ό³Έν :
class Obj : public GameEngineActor
{
public:
	// constrcuter destructer
	Obj();
	~Obj();

	// delete Function
	Obj(const Obj& _Other) = delete;
	Obj(Obj&& _Other) noexcept = delete;
	Obj& operator=(const Obj& _Other) = delete;
	Obj& operator=(Obj&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> Render;

protected:
	void Start();
	void Update(float _Delta) override;

private:

};

