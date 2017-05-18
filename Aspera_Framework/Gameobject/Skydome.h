#ifndef _SKYDOME_H_
#define _SKYDOME_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"
#include "../Component/ModelMesh.h"

class Skydome : public GameObject
{
public:
	Skydome();
	~Skydome();

	virtual bool Initialize();
	bool Initialize(char*);
	virtual void Shutdown();

private:
	Transform* m_transform;
	ModelMesh* m_modelMesh;
	Renderer* m_renderer;
	XMFLOAT4 m_apexColor, m_centerColor;
};

#endif _SKYDOME_H_