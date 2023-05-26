#pragma once

// 설명 :
class Overworld_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Overworld_Map();
	~Overworld_Map();

	// delete Function
	Overworld_Map(const Overworld_Map& _Other) = delete;
	Overworld_Map(Overworld_Map&& _Other) noexcept = delete;
	Overworld_Map& operator=(const Overworld_Map& _Other) = delete;
	Overworld_Map& operator=(Overworld_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	// 월드 부쉬 랜더러
	std::shared_ptr<class GameEngineSpriteRenderer> Overworld_Bush_LeftRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Overworld_Bush_RightRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Mausoleum_BushRenderPtr = nullptr;

	// 구조물 랜더러
	std::shared_ptr<class GameEngineSpriteRenderer> DockRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BoatRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LighthouseRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BuoyRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Tree_IslandRenderPtr = nullptr;

	// 다리 토퍼 랜더러
	std::shared_ptr<class GameEngineSpriteRenderer> MainBridge_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ClipBridge_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ForestBridge_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlaneBridge_FrontTopperRenderPtr = nullptr;

	// 계단 토퍼 랜더러
	std::shared_ptr<class GameEngineSpriteRenderer> BotanicStair_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RuseStair_TopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TreetopStair_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HouseStair_FrontTopperRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ZeppelinStair_TopperRenderPtr = nullptr;

	void RendererWorldPositionCheck();
};
