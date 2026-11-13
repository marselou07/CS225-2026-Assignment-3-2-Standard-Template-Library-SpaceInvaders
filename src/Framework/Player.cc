#include "Player.hh"



void Player::Update()
{
}

void Player::Draw()
{
	AEGfxRect(position.x , position.y , 0, size.x, size.y, color);
}

void Player::OnInputEvent(MoveEvent* mMoveEvent)
{
	if (mMoveEvent->MoveType == Type::MoveRight)
	{
		position.x += speed *AEGetFrameTime();
	}
	if (mMoveEvent->MoveType == Type::MoveLeft)
	{
		position.x -= speed * AEGetFrameTime();
	}
}
