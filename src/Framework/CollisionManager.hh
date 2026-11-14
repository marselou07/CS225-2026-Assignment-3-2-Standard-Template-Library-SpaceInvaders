#pragma once
#include "event.hh"
#include <functional>
#include <vector>
#include <string>
#include "AECore/inc/AEEngine.h"
class Enemy;
class Bullet;
class Player;
enum ColType {LeftWall,RightWall, BulletToEnemy, BulletToPlayer, BulletToWalls};
enum BeingType {BEnemy,BPlayer,EBullet,PBullet};
class  CollisionEvent : public Event
{
public:
	ColType col;
	BeingType Being;
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
	Bullet* bplayer = nullptr;
	Bullet* benemy = nullptr;

	Player* p = nullptr;
	Enemy* eny = nullptr;
};