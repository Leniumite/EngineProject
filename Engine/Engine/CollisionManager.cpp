#include "pch.h"
#include "framework.h"
#include "CollisionManager.h"

void CollisionManager::checkCollisions()
{
	for (size_t i = 0; i < _colliders.size()-1; i++)
	{
		Collider* col = _colliders[i];
		for (size_t j = i+1; j < _colliders.size(); j++)
		{
			Collider* othercol = _colliders[j];
		}
	}
}
