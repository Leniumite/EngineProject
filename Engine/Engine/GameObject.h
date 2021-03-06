#pragma once

using namespace std;

class GameObject
{
private:
	list<Component*> _components;
	Engine* _engine;

public:
	float _timeToDestroy = 0.0f;

	Transform* _transform;

	GameObject(Engine* engine);
	~GameObject();

	inline Engine* GetEngine() { return _engine; }

	void UpdateComponents();

	template<class T>
	T* AddComponent();

	inline list<Component*>& GetAllComponents() { return _components; }

	template<class T>
	T* GetComponent();

	template<class T>
	list<T*> GetComponentAllComponentsOfType();
};


template <class T>
T* GameObject::GetComponent() {
	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		T* temp = dynamic_cast<T*>(*it);
		if (temp != NULL)
		{
			return temp;
		}
	}
	return nullptr;
}

template <class T>
list<T*> GameObject::GetComponentAllComponentsOfType() {
	list<T*> components = list<T*>();
	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		T* temp = dynamic_cast<T*>(*it);
		if (temp != NULL)
		{
			components.push_back(temp);
		}
	}
	return components;
}

template<class T>
T* GameObject::AddComponent()
{
	if (is_base_of_v<Component, T>)
	{
		T* p = new T(this);
		p->InitComponent();

		_components.push_back(p);

		return p;
	}
	else
	{
		return NULL;
	}
}
