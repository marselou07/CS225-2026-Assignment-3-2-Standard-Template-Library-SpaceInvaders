#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
class Bullet : public Entity
{
public:
	Bullet(int x, int y, int sx, int sy) : position(x, y), scale(sx, sy) {}
	void Update() override;
	void Draw() override;
private:
	AEVec2 position;
	AEVec2 scale;
};