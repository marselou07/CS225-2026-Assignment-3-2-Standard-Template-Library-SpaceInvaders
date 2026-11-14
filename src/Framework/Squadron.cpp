#include "Squadron.hh"
#include "time.h"
void Enemy::Update()
{
	if (active)
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
		if (counter != 0 && !active)
		{
			counter--;
		}
		else if(counter == 0 && !active)
		{
			active = true;
		}
		if (CanShoot && shootTime == 0 && active)
		{
			enemyBullet->active = true;
			enemyBullet->position.x = pos.x;
			enemyBullet->position.y = pos.y - scale.y;
			CanShoot = false;
		}
		else if (CanShoot && shootTime != 0 && active)
		{
			shootTime--;
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
	if (mEvent->col == ColType::BulletToEnemy && mEvent->Being == BeingType::PBullet)
	{
		active = false;
		pos = startPos;
		MoveRight = true;
		counter = 10;
		shootTime = 5;
		CanShoot = true;
	}
	if (mEvent->col == ColType::BulletToWalls && mEvent->Being == BeingType::EBullet)
	{
		shootTime = 5;
		enemyBullet->active = false;
		CanShoot = true;

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
