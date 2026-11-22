#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
#include "EventManager.hh"
#include "CollisionManager.hh"
#include <algorithm> 
#include <vector>
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
	int speed = 90;
	int counter = 20;
public:
	void OnColEvent(CollisionEvent* mEvent);
	void Update() override;
	void Draw() override;
	AEVec2& GetPos() { return pos; }
	AEVec2& GetScale() { return scale; }
	bool isActive() { return active; }
	bool BulletNotShoot() { return enemyBullet->active; }
	void RestartPool();
	void Shoot();
	Enemy(AEVec2 pos,AEVec2 scale,int color,Bullet* ebullet);
};
class Squadron 
{

	int spacex = 80;
	int spacey = 40;
	bool IsAlive = true;
	int counter = 60;
public:
	std::vector<Enemy*> squadron;
	std::vector<Bullet*> sEnemyBullets;
	Squadron(AEVec2 pos,AEVec2 scale, int color, AEVec2 Bulletscale);
	void Update();
	void Draw();
	void RestartSq();
	bool IsALIVE() {
		return IsAlive;
	}
	void OnColEvent(CollisionEvent* mEvent);
};