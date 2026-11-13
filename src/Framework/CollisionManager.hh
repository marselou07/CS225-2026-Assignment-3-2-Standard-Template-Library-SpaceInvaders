#pragma once
#include "event.hh"
#include <functional>
#include <vector>
#include <string>
#include "AECore/inc/AEEngine.h"
class Player;
class Bullet;
enum ColType {LeftWall,RightWall, BulletToEnemy, BulletToPlayer,BulletToWalls};
class  CollisionEvent : public Event
{
public:
	ColType col;
};

typedef std::function<void(CollisionEvent* event)> OnColEvent;

class CollisionManager
{
protected:
	std::vector<OnColEvent> handlers;
public:
	void addHandler(OnColEvent event);
	void trigger(CollisionEvent* event);
	void update();
	Bullet* b = nullptr;
	Player* p = nullptr;
};