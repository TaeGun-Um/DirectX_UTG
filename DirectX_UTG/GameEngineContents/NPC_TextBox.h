#pragma once

class GameEngineFontRenderer;

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
		TailRenderPtr->GetTransform()->SetLocalPosition(_Value + float4{130, -80});
		ArrowRenderPtr->GetTransform()->SetLocalPosition(_Value + float4{ 170, -40 });
		BoxCurPosition = BoxRenderPtr->GetTransform()->GetWorldPosition();
	}

	bool RenderAlphaSetting(std::shared_ptr<GameEngineFontRenderer> _FontRender, float _DeltaTime);
	void BoxReset();

	void BoxScaleChange(float4 _Value)
	{
		BoxRenderPtr->GetTransform()->SetLocalScale(_Value);
	}

	float4 GetBoxCurPosition()
	{
		return BoxCurPosition;
	}

	float4 GetBoxScale()
	{
		return BoxRenderPtr->GetTransform()->GetLocalScale();
	}

	float4 SetBoxScale(float4 _Value)
	{
		BoxRenderPtr->GetTransform()->SetLocalScale({ _Value.x, _Value.y, 1 });
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

	float4 BoxCurPosition = float4::Zero;
	bool IsDown = false;
	bool IsEnd = false;
};

