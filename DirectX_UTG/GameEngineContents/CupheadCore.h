#pragma once

// Ό³Έν :
class CupheadCore
{
public:
	// constrcuter destructer
	CupheadCore();
	~CupheadCore();

	// delete Function
	CupheadCore(const CupheadCore& _Other) = delete;
	CupheadCore(CupheadCore&& _Other) noexcept = delete;
	CupheadCore& operator=(const CupheadCore& _Other) = delete;
	CupheadCore& operator=(CupheadCore&& _Other) noexcept = delete;

	static void GameStart();
	static void GameEnd();
	static void ContentsResourcesCreate();
	static void ContentsKeyBind();

protected:

private:
};

