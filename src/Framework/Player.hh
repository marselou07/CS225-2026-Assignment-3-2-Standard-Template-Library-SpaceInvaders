#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
#include "EventManager.hh"
#include "Bullet.hh"
class Player : public Entity
{
public:
	Player(AEVec2 pos, AEVec2 size, int color, Bullet* b) : position(pos), size(size)
		, color(color), bullet(b) {
	}
	void Update() override;
	void Draw() override;
	void OnInputEvent(GameEvent* mEvent);
	AEVec2 GetPos() { return position; }
	AEVec2 GetScale() { return size; }
private:
	AEVec2 position;
	AEVec2 size;
	int color;
	Bullet *bullet;
	int speed = 200;
	bool shoot = true;
};
