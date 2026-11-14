#include "CollisionManager.hh"
#include "Bullet.hh"
#include "Player.hh"
#include "Squadron.hh"

void CollisionManager::addHandler(OnColEvent event)
{
	handlers.push_back(event);
}

void CollisionManager::trigger(CollisionEvent* event)
{
	std::for_each(handlers.begin(), handlers.end(), [&event](OnColEvent& handler)
		{
			handler(event);

		});
}

void CollisionManager::update()
{
	int halfx = (int)AEGetSysWindowWidth() / 2;
	int halfy = (int)AEGetSysWindowHeight() / 2;
	if (bplayer->active)
	{
		if (bplayer->position.y + bplayer->scale.y >= halfy)
		{
			bplayer->active = false;
			CollisionEvent colT;
			colT.col = ColType::BulletToWalls;
			colT.Being = BeingType::PBullet;
			trigger(&colT);
		}
		if (AEStaticRectToStaticRect(&bplayer->position, bplayer->scale.x,
			bplayer->scale.y, &eny->GetPos(), eny->GetScale().x, eny->GetScale().y))
		{
			bplayer->active = false;
			CollisionEvent colT;
			colT.col = ColType::BulletToEnemy;
			colT.Being = BeingType::PBullet;
			trigger(&colT);
		}
	}
	if (benemy->active)
	{
		if (benemy->position.y - benemy->scale.y <= -halfy)
		{
			benemy->active = false;
			CollisionEvent colT;
			colT.col = ColType::BulletToWalls;
			colT.Being = BeingType::EBullet;
			trigger(&colT);
		}
		if (AEStaticRectToStaticRect(&benemy->position, benemy->scale.x,
			benemy->scale.y, &p->GetPos(), p->GetScale().x, p->GetScale().y))
		{
			benemy->active = false;
			CollisionEvent colT;
			colT.col = ColType::BulletToPlayer;
			colT.Being = BeingType::EBullet;
			trigger(&colT);
		}

	}
	if (p->GetPos().x + p->GetScale().x >= halfx)
	{
		CollisionEvent colT;
		colT.col = ColType::RightWall;
		colT.Being = BeingType::BPlayer;
		trigger(&colT);
	}
	if (p->GetPos().x - p->GetScale().x <= -halfx)
	{
		CollisionEvent colT;
		colT.col = ColType::LeftWall;
		colT.Being = BeingType::BPlayer;
		trigger(&colT);
	}
	if (eny->isActive())
	{
		if (eny->GetPos().x + eny->GetScale().x >= halfx)
		{
			CollisionEvent colT;
			colT.col = ColType::RightWall;
			colT.Being = BeingType::BEnemy;
			trigger(&colT);
		}
		if (eny->GetPos().x - eny->GetScale().x <= -halfx)
		{
			CollisionEvent colT;
			colT.col = ColType::LeftWall;
			colT.Being = BeingType::BEnemy;
			trigger(&colT);
		}
	}
}
