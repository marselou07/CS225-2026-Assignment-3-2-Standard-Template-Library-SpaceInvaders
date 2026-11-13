#include "Player.hh"



void Player::Update()
{
}

void Player::Draw()
{
	AEGfxRect(position.x , position.y , 0, size.x, size.y, color);
}

void Player::OnInputEvent(GameEvent* mEvent)
{
	if (mEvent->PlayerType == Type::MoveRight)
	{
		position.x += speed *AEGetFrameTime();
	}
	if (mEvent->PlayerType == Type::MoveLeft)
	{
		position.x -= speed * AEGetFrameTime();
	}
	if (mEvent->PlayerType == Type::Shoot && shoot)
	{
		bullet->active = true;
		bullet->position.x = position.x ;
		bullet->position.y = position.y+ size.y;
		shoot = false;
	}

}
