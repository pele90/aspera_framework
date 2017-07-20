#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(char* name)
{
	m_name = name;
}

GameObject::GameObject(const GameObject&) {}

GameObject::~GameObject() {}

bool GameObject::Initialize()
{
	m_Components = vector<Component*>();

	return true;
}

void GameObject::Shutdown()
{
	for (vector<Component*>::iterator iter = m_Components.begin(); iter != m_Components.end(); ++iter)
		(*iter)->Shutdown();

	m_Components.clear();
}

char* GameObject::GetName()
{
	return m_name;
}

void GameObject::AddComponent(Component* component)
{
	m_Components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	vector<Component*>::iterator iter = find_if(m_Components.begin(), m_Components.end(), [component](Component* p)->bool { return component->GetIndex() == p->GetIndex(); });

	if (iter != m_Components.end())
	{
		(*iter)->Shutdown();
		m_Components.erase(iter);
	}
}

vector<Component*> GameObject::GetComponents()
{
	return m_Components;
}