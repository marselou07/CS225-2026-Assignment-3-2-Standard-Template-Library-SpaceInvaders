#include "Squadron.hh"
void Enemy::Update()
{
	if (MoveRight)
	{
		pos.x += speed *AEGetFrameTime();
	}
	else if (!MoveRight)
	{
		pos.x -= speed * AEGetFrameTime();

	}
}

void Enemy::Draw()
{
	if (active)
	{
		AEGfxRect(pos.x, pos.y, 0, scale.x, scale.y, color);
	}
}
Enemy::Enemy(AEVec2 pos, AEVec2 scale, int color, Bullet* ebullet)
{
	this->pos = pos;
	this->startPos = pos;
	this->scale = scale;
	this->color = color;

	enemyBullet = ebullet;
}

void Enemy::OnColEvent(CollisionEvent* mEvent)
{
	if (mEvent->col == ColType::BulletToEnemy)
	{

	}
	if (mEvent->col == ColType::RightWall && mEvent->Being == BeingType::BEnemy)
	{
		MoveRight = false;
		pos.y -= 20;
		
	}
	if (mEvent->col == ColType::LeftWall && mEvent->Being == BeingType::BEnemy)
	{
		MoveRight = true;
		pos.y -= 20;

	}
}





Squadron::Squadron(AEVec2 pos, AEVec2 scale, int color)
{
	
}
