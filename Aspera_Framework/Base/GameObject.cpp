#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(char* name)
{
	m_name = name;
	m_active = true;
	m_selected = false;
}

GameObject::GameObject(const GameObject&) {}

GameObject::~GameObject() {}

bool GameObject::Initialize()
{
	m_components = vector<Component*>();

	return true;
}

void GameObject::Shutdown()
{
	for (vector<Component*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
		(*iter)->Shutdown();

	m_components.clear();
}

void GameObject::AddComponent(Component* component)
{
	m_components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	vector<Component*>::iterator iter = find_if(m_components.begin(), m_components.end(), [component](Component* p)->bool { return component->GetIndex() == p->GetIndex(); });

	if (iter != m_components.end())
	{
		(*iter)->Shutdown();
		m_components.erase(iter);
	}
}

vector<Component*> GameObject::GetComponents()
{
	return m_components;
}

char* GameObject::GetName()
{
	return m_name;
}

void GameObject::SetName(char* name)
{
	m_name = name;
}

bool GameObject::IsActive()
{
	return m_active;
}

void GameObject::SetActive(bool value)
{
	m_active = value;
}

bool GameObject::IsSelected()
{
	return m_selected;
}

void GameObject::SetSelected(bool value)
{
	m_selected = value;
}