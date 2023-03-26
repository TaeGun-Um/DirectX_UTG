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
float Scale = 100.0f;

void Player::Render(float _Delta)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	const int VertexCount = 24;

	float4 Pos = { 640, 360 };

	float4 ArrVertex[VertexCount];

	ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
	ArrVertex[1] = { 0.5f, -0.5f, 0.5f };
	ArrVertex[2] = { 0.5f, 0.5f, 0.5f };
	ArrVertex[3] = { -0.5f, 0.5f, 0.5f };


	// Polygon(Dc, &ArrPoint[i * 4], 4);

};