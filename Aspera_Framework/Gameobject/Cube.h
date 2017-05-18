#ifndef _CUBE_H_
#define _CUBE_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"
#include "../Component/ModelMesh.h"

class Cube : public GameObject
{
public:
	Cube();
	~Cube();

	virtual bool Initialize();
	bool Initialize(char*);
	virtual void Shutdown();

private:
	Renderer* m_renderer;
	ModelMesh* m_model;
	Transform* m_transform;

};

#endif // !_CUBE_H_
