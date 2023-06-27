#include "PrecompileHeader.h"
#include "EndingLevel.h"

#include "OldFilm.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Start()
{
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