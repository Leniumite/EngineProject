#include "pch.h"
#include "framework.h"

LightComponent::LightComponent(GameObject* gameObject) : Component(gameObject)
{
}



void LightComponent::InitComponent()
{
	ZeroMemory(&_light, sizeof(_light));
	_d3ddev->SetLight(m_id, &_light);    // send the light struct properties to the light identified by its m_ID
	_d3ddev->LightEnable(m_id, TRUE);    // turn on light at given ID
}

void LightComponent::SetColor(D3DXCOLOR newColor)
{
	_light.Ambient = newColor;
	_d3ddev->SetLight(m_id, &_light);
}

void LightComponent::SetDirection(D3DXVECTOR3 newDirection)
{
	_light.Direction = newDirection;
	_d3ddev->SetLight(m_id, &_light);
}

void LightComponent::SetRange(float newRange)
{
	_light.Range = newRange;
	_d3ddev->SetLight(m_id, &_light);
}

void LightComponent::SetType(D3DLIGHTTYPE newLightType)
{
	_light.Type = newLightType;
	_d3ddev->SetLight(m_id, &_light);
}

void LightComponent::SetInnerAngle(float newAngle)
{
	_light.Theta = newAngle;
}


