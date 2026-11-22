#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
#include "EventManager.hh"
#include "CollisionManager.hh"
#include "Bullet.hh"
class Player : public Entity
{
public:
	Player(AEVec2 pos, AEVec2 size, int color, Bullet* b) : position(pos), size(size)
		, color(color), bullet(b), originalpos(pos){
	}
	void Update() override;
	void Draw() override;
	void OnInputEvent(GameEvent* mEvent);
	void OnColEvent(CollisionEvent* mEvent);
	AEVec2& GetPos() { return position; }
	void Restart();
	AEVec2& GetScale() { return size; }
	bool Alive = true;
private:
	AEVec2 position;
	AEVec2 size;
	int color;
	AEVec2 originalpos;
	Bullet *bullet;
	int speed = 200;
	bool shoot = true;
};
