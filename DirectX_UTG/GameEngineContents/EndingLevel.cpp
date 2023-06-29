#include "PrecompileHeader.h"
#include "EndingLevel.h"

#include <GameEngineCore/BlurEffect.h>
#include "OldFilm.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Start()
{
	GetLastTarget()->CreateEffect<BlurEffect>();
	GetLastTarget()->CreateEffect<OldFilm>();
}
void EndingLevel::Update(float _DeltaTime)
{

}

void EndingLevel::LevelChangeStart()
{

}
void EndingLevel::LevelChangeEnd()
{

}