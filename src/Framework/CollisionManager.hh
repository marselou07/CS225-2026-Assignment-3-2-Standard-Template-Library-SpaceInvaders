#pragma once
#include "event.hh"
#include <functional>
#include <vector>
#include <string>
#include "AECore/inc/AEEngine.h"
class Enemy;
class Bullet;
class Player;
class Squadron;
enum ColType {LeftWall,RightWall, BulletToEnemy, BulletToPlayer, BulletToWalls};
enum BeingType {Enemy_,Player_,EBullet,PBullet};
class  CollisionEvent : public Event
{
public:
	ColType col;
	BeingType Being;
	Enemy* e;
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
	CollisionManager();
	Bullet* bplayer = nullptr;
	Player* p = nullptr;

	Squadron* squad = nullptr;
};