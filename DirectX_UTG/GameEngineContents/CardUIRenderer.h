#pragma once

#include <GameEngineCore/GameEngineUIRenderer.h>

// Ό³Έν :
class CardUIRenderer : public GameEngineUIRenderer
{
public:
	// constrcuter destructer
	CardUIRenderer();
	~CardUIRenderer();

	// delete Function
	CardUIRenderer(const CardUIRenderer& _Other) = delete;
	CardUIRenderer(CardUIRenderer&& _Other) noexcept = delete;
	CardUIRenderer& operator=(const CardUIRenderer& _Other) = delete;
	CardUIRenderer& operator=(CardUIRenderer&& _Other) noexcept = delete;

	void SetCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY);
	void SetScaleToCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY);

protected:
	void Start() override;

private:

};

