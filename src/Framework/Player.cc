#include "Player.hh"
/******************************************************************************
filename    CollisionManager.cc
author      Markel Susial de la fuente
DP email    markel.susial@digipen.edu
course      cs225
assignment  3.2
due date    17/11/2026

Brief Description: handle the collisions of everything
******************************************************************************/

/**
 * Update
 * @param context: do nothing 
 * @return nothing
 */
void Player::Update()
{
}
/**
 * Draw
 * @param context: draw the player
 * @return nothing
 */
void Player::Draw()
{
	AEGfxRect(position.x , position.y , 0, size.x, size.y, color);
}
/**
 * OnInputEvent
 * @param context: depends of each event it will
 * perform different task
 * GameEvent* mEvent: the type of input event
 * @return nothing
 */
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
/**
 * OnColEvent
 * @param context: handle the collision of
 * the player
 * CollisionEvent* mEvent: the type of col event
 * @return nothing
 */
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
		position.x = (int)AEGetSysWindowWidth() / 2 - size.x;
	}
	if (mEvent->col == ColType::LeftWall && mEvent->Being == BeingType::Player_)
	{
		position.x = -(int)AEGetSysWindowWidth() / 2 + size.x;
	}
}
/**
 * Restart
 * @param context: restart the player
 * @return nothing
 */
void Player::Restart()
{
	position = originalpos;
	shoot = true;
	bullet->active = false;
}
