#ifndef _INSTANCEDCUBE_H_
#define _INSTANCEDCUBE_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"
#include "../Component/InstancingMesh.h"

class InstancedCube : public GameObject
{
public:
	InstancedCube();
	~InstancedCube();

	virtual bool Initialize();
	bool Initialize(char*);
	virtual void Shutdown();

private:
	Renderer* m_renderer;
	InstancingMesh* m_model;
	Transform* m_transform;

};

#endif // !_INSTANCEDCUBE_H_
