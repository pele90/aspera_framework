#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Component.h"
#include <algorithm>
#include <typeinfo>

class GameObject
{
public:
	GameObject();
	GameObject(char *);
	GameObject(const GameObject&);
	~GameObject();

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	void AddComponent(Component*);
	void RemoveComponent(Component*);

	char* GetName();
	void SetName(char* name);
	bool IsActive();
	void SetActive(bool value);
	bool IsSelected();
	void SetSelected(bool value);

	/*template<typename T>
	T* GetComponent(char* type)
	{
		for (vector<Component*>::iterator iter = m_Components.begin(); iter != m_Components.end(); ++iter)
		{
			if ((*iter)->GetType() == type)
			{
				return (T*)(*iter);
			}
		}

		return NULL;
	}*/

	template<typename T>
	T* GetComponent()
	{
		T* retValue = NULL;
		for (vector<Component*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			retValue = dynamic_cast<T*>((*iter));
			if (retValue != NULL)
			{
				return (T*)(*iter);
			}
		}

		return NULL;
	}


	vector<Component*> GetComponents();


private:

private:
	char* m_name;
	vector<Component*> m_components;
	bool m_active;
	bool m_selected;
};

#endif // !_GAMEOBJECT_H_

