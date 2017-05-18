#ifndef PREFAB_H_
#define PREFAB_H_

#include "GameObject.h"
#include "Component.h"
#include <vector>

class Prefab : public GameObject
{
public:
	Prefab();
	~Prefab();

	virtual bool Initialize();
	virtual void Shutdown();

private:
	std::vector<Component> m_components;
};

#endif // !PREFAB_H_

