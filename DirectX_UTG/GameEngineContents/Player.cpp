#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Update(float _Delta)
{

}

float Angle = 0.0f;

void Player::Render(float _Delta)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	if (1 == Count)
	{
		Count = 0;

		//ArrVertex[0] = { -50, -50 };
		//ArrVertex[1] = { 50, -50 };
		//ArrVertex[2] = { 50, 50 };
		//ArrVertex[3] = { -50, 50 };

		//ArrVertex[0] += Pos;
		//ArrVertex[1] += Pos;
		//ArrVertex[2] += Pos;
		//ArrVertex[3] += Pos;

	}

	ArrVertex[0] = { -50, -50 };
	ArrVertex[1] = { 50, -50 };
	ArrVertex[2] = { 50, 50 };
	ArrVertex[3] = { -50, 50 };

	const int VertexCount = 4;

	POINT ArrPoint[VertexCount];

	Angle += _Delta * 360.0f;

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i].RotaitonZDeg(Angle);
		ArrVertex[i] += Pos;
		//ArrVertex[i] += {1 * _Delta, 0};

		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	Polygon(Dc, ArrPoint, VertexCount);
};