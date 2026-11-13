#include "CollisionManager.hh"
#include "Bullet.hh"
#include "Player.hh"
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
	if (b->active)
	{
		if (b->position.y + b->scale.y >= halfy)
		{
			CollisionEvent colT;
			colT.col = ColType::BulletToWalls;
			trigger(&colT);
		}
	}
	if (p->GetPos().x + p->GetScale().x >= halfx)
	{
		CollisionEvent colT;
		colT.col = ColType::RightWall;
		trigger(&colT);
	}
	if (p->GetPos().x - p->GetScale().x <= -halfx)
	{
		CollisionEvent colT;
		colT.col = ColType::LeftWall;
		trigger(&colT);
	}
}
