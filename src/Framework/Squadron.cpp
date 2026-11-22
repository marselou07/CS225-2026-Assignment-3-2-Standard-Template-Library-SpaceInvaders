#include "Squadron.hh"
#include <ctime>
#include <random>
/******************************************************************************
filename    Squadron.cc
author      Markel Susial de la fuente
DP email    markel.susial@digipen.edu
course      cs225
assignment  3.2
due date    17/11/2026

Brief Description: create the logic of the enemy and a
squadron
******************************************************************************/
/**
 * Update
 * @param context: update the enemiy movement
 * @return nothing
 */
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

}
/**
 * Draw
 * @param context: draw the enemy
 * @return nothing
 */
void Enemy::Draw()
{
	if (active)
	{
		AEGfxRect(pos.x, pos.y, 0, scale.x, scale.y, color);
	}
}
/**
 * RestartPool
 * @param context: for each enemy restart it
 * @return nothing
 */
void Enemy::RestartPool()
{
	pos = startPos;
	active = true;
	enemyBullet->active = false;
	MoveRight = true;
}
/**
 * Shoot
 * @param context: shoot an enemy bullet
 * @return nothing
 */
void Enemy::Shoot()
{
	if (active == true)
	{
		if (!this->enemyBullet->active )
		{
			enemyBullet->active = true;
			enemyBullet->position.x = pos.x;
			enemyBullet->position.y = pos.y - scale.y;
		}
	}
}
/**
 * Constructor
 * @param context: initialize the enemy
 * @return nothing
 */
Enemy::Enemy(AEVec2 pos, AEVec2 scale, int color, Bullet* ebullet)
{
	this->pos = pos;
	this->startPos = pos;
	this->scale = scale;
	this->color = color;
	enemyBullet = ebullet;
}

/**
 * OnColEvent
 * @param context: handle the collision of
 * the enemies
 * CollisionEvent* mEvent: the type of col event
 * @return nothing
 */
void Enemy::OnColEvent(CollisionEvent* mEvent)
{
	//The squadron will send this information to an specific enemy
	if (mEvent->col == ColType::BulletToEnemy && mEvent->Being == BeingType::PBullet
		&& mEvent->e == this)
	{
		active = false;
	}
	if (mEvent->col == ColType::BulletToWalls && mEvent->Being == BeingType::EBullet)
	{
		enemyBullet->active = false;
		CanShoot = true;

	}
	if (mEvent->col == ColType::RightWall && mEvent->Being == BeingType::Enemy_)
	{
		MoveRight = false;
		pos.y -= 10;
		
	}
	if (mEvent->col == ColType::LeftWall && mEvent->Being == BeingType::Enemy_)
	{
		MoveRight = true;
		pos.y -= 20;

	}
}
//--------------------------------
//Squadron part

/**
 * Squadron
 * @param context: constructor initialize each enemy and enemy bullet
 * @return nothing
 */
Squadron::Squadron(AEVec2 pos, AEVec2 scale, int color, AEVec2 Bulletscale)
{
	std::srand(std::time(0));
	squadron.resize(16);
	sEnemyBullets.resize(16);
	int index = 0;
	std::for_each(sEnemyBullets.begin(), sEnemyBullets.end(), [ color, Bulletscale,this](Bullet*& b)
		{
			b = new Bullet(Bulletscale, BulletType::EnemyBullet, color);



		});
	std::for_each(squadron.begin(), squadron.end(), [pos, scale, color, &index, this](Enemy *& e)
		{
			int row = index / 4;
			int coll = index % 4;
			float x = pos.x + coll * this->spacex;
			float y = pos.y - row * this->spacey;
			e = new Enemy(AEVec2(x, y), scale, color, this->sEnemyBullets[index]);



			index++;
		});
}
/**
 * Update
 * @param context:update the squadron
 * @return nothing
 */
void Squadron::Update()
{
	std::for_each(squadron.begin(), squadron.end(), [](Enemy* e)
		{
			e->Update();
		});
	std::for_each(sEnemyBullets.begin(), sEnemyBullets.end(), [](Bullet* b)
		{
			b->Update();
		});
	bool Is = std::all_of(squadron.begin(), squadron.end(), [](Enemy * e) 
		{
			return !(e->isActive());
		});
	if (Is)
	{
		RestartSq();
	}
	if (counter != 0)
	{
		counter--;
	}
	else
	{
		int rpos = std::rand() % squadron.size();
		if (squadron[rpos]->isActive() && squadron[rpos]->BulletNotShoot() == false)
		{
			squadron[rpos]->Shoot();
			counter = 60;
		}
	}

	
}
/**
 * Draw
 * @param context:draw all enemies and their bullets
 * @return nothing
 */
void Squadron::Draw()
{
	std::for_each(squadron.begin(), squadron.end(), [](Enemy* e)
		{
			e->Draw();
		});
	std::for_each(sEnemyBullets.begin(), sEnemyBullets.end(), [](Bullet* b)
		{
			b->Draw();
		});
}
/**
 * RestartSq
 * @param context: restart all enemies
 * @return nothing
 */
void Squadron::RestartSq()
{

	std::for_each(squadron.begin(), squadron.end(), [](Enemy* e)
			{
				e->RestartPool();


		});
	
}
/**
 * OnColEvent
 * @param context: handle the collision of
 * all the enemy squadron
 * CollisionEvent* mEvent: the type of col event
 * @return nothing
 */
void Squadron::OnColEvent(CollisionEvent* mEvent)
{
	if (mEvent->col == ColType::RightWall && mEvent->Being == BeingType::Enemy_)
	{
		std::for_each(squadron.begin(), squadron.end(), [mEvent](Enemy* e)
			{

				e->OnColEvent(mEvent);
				

			});
	}
	if (mEvent->col == ColType::LeftWall && mEvent->Being == BeingType::Enemy_)
	{
		std::for_each(squadron.begin(), squadron.end(), [mEvent](Enemy* e)
			{

				e->OnColEvent(mEvent);


			});
	}
	if (mEvent->col == ColType::BulletToEnemy && mEvent->Being == BeingType::PBullet)
	{
		std::for_each(squadron.begin(), squadron.end(), [mEvent](Enemy *e)
		{
				if (e == mEvent->e)
				{
					e->OnColEvent(mEvent);
				}
			 
		});
	}
}
