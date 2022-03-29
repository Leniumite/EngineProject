#pragma once

struct PARTICLEVERTEX {
	D3DXVECTOR3 position;
	D3DXCOLOR diffuse;
	D3DXCOLOR ambient;
};


class Particle
{

public:

	float _lifeTime;
	float _age;
	D3DXCOLOR _color;
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
	bool _isAlive;

	Particle();

	void UpdatePosition(float deltaTime);
	void UpdateColor();
	bool UpdateLifeTime(float deltaTime);




};
