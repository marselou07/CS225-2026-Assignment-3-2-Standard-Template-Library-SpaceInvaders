#include "Bullet.hh"

void Bullet::Update()
{
	if (active)
	{
		if (this->type == BulletType::PlayerBullet)
		{
			position.y += speed * AEGetFrameTime();
		}
		else
		{
			position.y -= speed * AEGetFrameTime();
		}
	}

}

void Bullet::Draw()
{
	if (active)
	{
		AEGfxRect(position.x, position.y, 0, scale.x, scale.y, color);
	}
	
}

void Bullet::Deactive()
{
	active = false;
}
