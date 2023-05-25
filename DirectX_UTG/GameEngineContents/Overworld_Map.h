#pragma once

// ���� :
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
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

	// ���� �ν� ������
	std::shared_ptr<class GameEngineSpriteRenderer> Overworld_Bush_LeftRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> Overworld_Bush_RightRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> Mausoleum_BushRenderPtr;

	// ������ ������
	std::shared_ptr<class GameEngineSpriteRenderer> DockRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> BoatRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> LighthouseRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> BuoyRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> Tree_IslandRenderPtr;

	// �ٸ� ���� ������
	std::shared_ptr<class GameEngineSpriteRenderer> MainBridge_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> ClipBridge_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> ForestBridge_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlaneBridge_FrontTopperRenderPtr;

	// ��� ���� ������
	std::shared_ptr<class GameEngineSpriteRenderer> BotanicStair_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> RuseStair_TopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> TreetopStair_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> HouseStair_FrontTopperRenderPtr;
	std::shared_ptr<class GameEngineSpriteRenderer> ZeppelinStair_TopperRenderPtr;
};
