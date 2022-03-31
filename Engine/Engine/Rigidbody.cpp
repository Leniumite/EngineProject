#include "pch.h"
#include "framework.h"

Rigidbody::Rigidbody(GameObject* gameObject) : Component(gameObject)
{
	
}

Rigidbody::~Rigidbody()
{
	mesh = NULL;
	transform = NULL;
}

void Rigidbody::Init()
{
	transform = _gameObject->_transform;
	IsInit = TRUE;
	pos = transform->GetPosition();
	SetGravity(TRUE);
}

void Rigidbody::Update()
{
	if (IsInit == FALSE) {
		Init();
	}
	velocity += acc * _engine->GetTimer()->deltaTime;
	pos += velocity * _engine->GetTimer()->deltaTime;
	transform->ChangePosition(pos);

	

}

void Rigidbody::SetGravity(bool b)
{
	if (gravityEnabled !=b)
	{
		if (b==true)
		{
			acc.y -= g;
			gravityEnabled = TRUE;
		}
		else if (b==false)
		{
			acc.y += g;
			gravityEnabled = FALSE;
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


