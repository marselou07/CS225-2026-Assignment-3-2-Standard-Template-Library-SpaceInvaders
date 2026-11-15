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

void Player::OnColEvent(CollisionEvent* mEvent)
{
	if (mEvent->col == ColType::BulletToWalls && mEvent->Being == BeingType::PBullet)
	{
		shoot = true;
		bullet->Deactive();
	}
	if (mEvent->col == ColType::BulletToEnemy && mEvent->Being == BeingType::PBullet)
	{
		shoot = true;
		bullet->Deactive();
	}
	if (mEvent->col == ColType::BulletToPlayer && mEvent->Being == BeingType::EBullet)
	{
		Alive = false;
	}
	if (mEvent->col == ColType::RightWall && mEvent->Being == BeingType::Player_)
	{
		position.x = (int)AEGetSysWindowWidth()/2  - size.x;
	}
	if (mEvent->col == ColType::LeftWall && mEvent->Being == BeingType::Player_)
	{
		position.x = -(int)AEGetSysWindowWidth() / 2 + size.x;
	}
}
