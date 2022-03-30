#include "pch.h"
#include "framework.h"

void Particle::UpdatePosition(float deltaTime)
{
	_velocity += _acceleration * deltaTime;
	_position += _velocity * deltaTime;
}

void Particle::UpdateColor()
{
	float alpha = ((_lifeTime - _age) / _lifeTime);
	if (alpha < 0.0f)
		alpha = 0.0f;
	else if ( alpha>1.0f )
		alpha = 1.0f;
	_color.a = alpha;
}

bool Particle::UpdateLifeTime(float deltaTime)
{
	_age += deltaTime;

	if (_age >= _lifeTime)
	{
		return false;
	}

	return true;
}

Particle::Particle()
{
	_lifeTime = 0.0f;
	_isAlive = false;
	_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_age = 0.0f;
}