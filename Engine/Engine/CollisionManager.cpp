#include "pch.h"
#include "framework.h"
#include "CollisionManager.h"

void CollisionManager::checkCollisions()
{
	if (_colliders.size()==0)
	{
		return;
	}
	hasCollide = FALSE;
	for (size_t i = 0; i < _colliders.size()-1; i++)
	{

		Collider* col = _colliders[i];
		for (size_t j = i+1; j < _colliders.size(); j++)
		{
			Collider* othercol = _colliders[j];

			BoxCollider* bOtherCollider = othercol->_gameObject->GetComponent<BoxCollider>();
			BoxCollider* bCollider = col->_gameObject->GetComponent<BoxCollider>();
			SphereCollider* sCollider = col->_gameObject->GetComponent<SphereCollider>();
			SphereCollider* sOtherCollider = othercol->_gameObject->GetComponent<SphereCollider>();
			if (bCollider != NULL && bOtherCollider != NULL)
			{
				//hasCollide = hasCollide || BoxBoxCollision(bOtherCollider, bCollider);
			}
			else if (sCollider != NULL && sOtherCollider != NULL)
			{
				//hasCollide = hasCollide || SphereSphereCollision(sCollider, sOtherCollider);
			}
			else if (sCollider != NULL && bOtherCollider != NULL && sCollider->isEnable == TRUE && bOtherCollider->isEnable == TRUE)
			{
				if (BoxSphereCollision(bOtherCollider, sCollider)) {
					for (Listener* listener : sCollider->collisionListeners)
					{
						listener->OnRaise();
					}
					for (Listener* listener : bOtherCollider->collisionListeners)
					{
						listener->OnRaise();
					}
				}
			}
			else if (bCollider != NULL && sOtherCollider != NULL && bCollider->isEnable == TRUE && sOtherCollider->isEnable == TRUE)
			{
				if (BoxSphereCollision(bCollider, sOtherCollider)) {
					for (Listener* listener : bCollider->collisionListeners)
					{
						listener->OnRaise();
					}
					for (Listener* listener : sOtherCollider->collisionListeners)
					{
						listener->OnRaise();
					}
				}
			}
			
			othercol = NULL;
			bOtherCollider = NULL;
			bCollider = NULL;
			sCollider = NULL;
			sOtherCollider = NULL;
		}
	}
}

bool CollisionManager::SphereSphereCollision(SphereCollider* col1, SphereCollider* col2)
{

	D3DXVECTOR3 distvec = (col1->_center - col2->_center);
	float dist = sqrtf(distvec.x * distvec.x +
		distvec.y * distvec.y +
		distvec.z * distvec.z);


	if (dist> col1->_d+col2->_d)
	{
		return true;
	}
	return false;
}

bool CollisionManager::BoxBoxCollision(BoxCollider* col1, BoxCollider* col2)
{
	D3DXVECTOR3 dist = D3DXVECTOR3 (fabs(&col1->_center.x - &col2->_center.x),
									fabs(&col1->_center.y - &col2->_center.y),
									fabs(&col1->_center.z - &col2->_center.z));

	if (D3DXVec3Dot(&dist, &Right)  < col1->_distX * .5f + col2->_distX * .5f &&
		D3DXVec3Dot(&dist, &Up)     < col1->_distY * .5f + col2->_distY * .5f &&
		D3DXVec3Dot(&dist, &Forward)< col1->_distZ * .5f + col2->_distZ * .5f)
	{
		return true;
	}


	return false;
}

bool CollisionManager::BoxSphereCollision(BoxCollider* box, SphereCollider* sphere)
{
	D3DXVECTOR3 closestPoint = D3DXVECTOR3(fmaxf(box->_posMin.x, fminf(sphere->_center.x, box->_posMax.x)),
							               fmaxf(box->_posMin.y, fminf(sphere->_center.y, box->_posMax.y)),
										   fmaxf(box->_posMin.z, fminf(sphere->_center.z, box->_posMax.z)));
	if (sqrtf( (closestPoint.x - sphere->_center.x) * (closestPoint.x - sphere->_center.x)+
			   (closestPoint.y - sphere->_center.y) * (closestPoint.y - sphere->_center.y)+
			   (closestPoint.z - sphere->_center.z) * (closestPoint.z - sphere->_center.z)) < sphere->_d*.5f )
	{
		
		return true;
	}

	return false;
}

void CollisionManager::AddCollider(Collider* col)
{
	_colliders.push_back(col);
}

void CollisionManager::RemoveCollider(Collider* col)
{
	_colliders.erase(std::remove(_colliders.begin(), _colliders.end(), col), _colliders.end());
}




