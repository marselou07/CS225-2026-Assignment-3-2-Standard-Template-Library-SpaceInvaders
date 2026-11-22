#include "Bullet.hh"
/******************************************************************************
filename    Bullet.cc
author      Markel Susial de la fuente
DP email    markel.susial@digipen.edu
course      cs225
assignment  3.2
due date    17/11/2026

Brief Description: create the logic of bullets
******************************************************************************/
/**
 * Update
 * @param context: update the bullet movement
 * @return nothing
 */
void Bullet::Update()
{
	if (active)
	{
		if (this->type == BulletType::PlayerBullet)
		{
			position.y += speed * AEGetFrameTime();
		}
		else if(this->type == BulletType::EnemyBullet)
		{
			position.y -= speed * AEGetFrameTime();
		}
	}

}
/**
 * Draw
 * @param context: draw the bullets
 * @return nothing
 */
void Bullet::Draw()
{
	if (active)
	{
		AEGfxRect(position.x, position.y, 0, scale.x, scale.y, color);
	}
	
}
/**
 * Draw
 * @param context: dactive the bullets
 * @return nothing
 */
void Bullet::Deactive()
{
	active = false;
}
