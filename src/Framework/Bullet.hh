#pragma once
#include "event.hh"
#include "entity.hh"
#include <AEEngine.h>
enum BulletType {EnemyBullet, PlayerBullet};
class Bullet : public Entity
{
public:
    Bullet( int sx, int sy, BulletType type, int color) : scale(sx, sy),
        type(type),color(color)
    {}
    void Update() override;
    void Draw() override;
    void Deactive();
    AEVec2 position;
    AEVec2 scale;
    float speed = 270.f;
    int color;
    bool active = false;
    BulletType type;
};