#pragma once

// Ό³Έν :
class NPC_TextBox : public GameEngineActor
{
public:
	// constrcuter destructer
	NPC_TextBox();
	~NPC_TextBox();

	// delete Function
	NPC_TextBox(const NPC_TextBox& _Other) = delete;
	NPC_TextBox(NPC_TextBox&& _Other) noexcept = delete;
	NPC_TextBox& operator=(const NPC_TextBox& _Other) = delete;
	NPC_TextBox& operator=(NPC_TextBox&& _Other) noexcept = delete;

	void LocalPositionSetting(float4 _Value)
	{
		BoxRenderPtr->GetTransform()->SetLocalPosition(_Value);
		TailRenderPtr->GetTransform()->SetLocalPosition(_Value);
		ArrowRenderPtr->GetTransform()->SetLocalPosition(_Value);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BoxRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TailRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ArrowRenderPtr = nullptr;

	void TextBoxInitSetting();
};

