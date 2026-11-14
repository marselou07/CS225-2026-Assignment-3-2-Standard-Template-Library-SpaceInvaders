#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
#include "EventManager.hh"
#include "CollisionManager.hh"
#include "Bullet.hh"
class Enemy : public Entity
{
	AEVec2 pos;
	AEVec2 scale;
	AEVec2 startPos;
	int color;
	bool active = true;
	bool CanShoot = true;
	bool MoveRight = true;
	Bullet* enemyBullet;
	int speed = 100;
public:
	void OnColEvent(CollisionEvent* mEvent);
	void Update() override;
	void Draw() override;
	AEVec2& GetPos() { return pos; }
	AEVec2& GetScale() { return scale; }
	bool isActive() { return active; }
	Enemy(AEVec2 pos,AEVec2 scale,int color,Bullet* ebullet);
};
class Squadron
{
	std::vector<Enemy> squadron;
public:
	Squadron(AEVec2 pos,AEVec2 scale, int color);
};