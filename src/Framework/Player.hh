#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
#include "PlayerEventManager.hh"
class Player : public Entity
{
public:
	Player(AEVec2 pos, AEVec2 size, int color) : position(pos) , size(size), color(color){}
	void Update() override;
	void Draw() override;
	void OnInputEvent(MoveEvent* mMoveEvent);
private:
	AEVec2 position;
	AEVec2 size;
	int speed = 200;
	int color;
};
