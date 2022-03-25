#include "pch.h"
#include "framework.h"

void Particle::UpdatePosition(float deltaTime)
{
	_velocity += _acceleration;
	_position += _velocity;
}

void Particle::UpdateColor()
{
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
	_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	_age = 0.0f;
}