#include "pch.h"
#include "framework.h"
#include "Rigidbody.h"

void Rigidbody::Init()
{
	transform = _gameObject->_transform;
	timer = _engine->GetTimer();
}

void Rigidbody::Update()
{
	velocity += acc * timer->deltaTime;
	pos += velocity * timer->deltaTime;
	transform->ChangePosition(pos);

}

void Rigidbody::SetGravity(bool b)
{
	if (gravityEnabled !=b)
	{
		if (b==true)
		{
			acc.y += g;
		}
		else if (b==false)
		{
			acc.y -= g;
		}
		
	}
}

void Rigidbody::AddVelocity(D3DXVECTOR3 vvect)
{
	velocity += vvect;
}

void Rigidbody::AddVelocityX(float vx)
{
	velocity.x += vx;
}

void Rigidbody::AddVelocityY(float vy)
{
	velocity.y += vy;
}

void Rigidbody::AddVelocityZ(float vz)
{
	velocity.z += vz;
}

void Rigidbody::AddForce(D3DXVECTOR3 avect)
{
	acc += avect;
}

void Rigidbody::AddForceX(float ax)
{
	acc.x += ax;
}

void Rigidbody::AddForceY(float ay)
{
	acc.y += ay;
}

void Rigidbody::AddForceZ(float az)
{
	acc.z += az;
}


