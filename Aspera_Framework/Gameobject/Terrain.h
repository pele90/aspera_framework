#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"
#include "../Component/TerrainMesh.h"

class Terrain : public GameObject
{
public:
	Terrain();
	~Terrain();

	virtual bool Initialize();
	bool Initialize(char*);
	virtual void Shutdown();

private:
	Transform* m_transform;
	TerrainMesh* m_terrainMesh;
	Renderer* m_renderer;
	
};


#endif // !_TERRAIN_H_

