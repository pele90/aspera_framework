#ifndef _DIRECTIONAL_LIGHT
#define _DIRECTIONAL_LIGHT

#include "..\Component\Transform.h"
#include "..\Component\Light.h"
#include "..\Base\GameObject.h"
#include "..\Component\ModelMesh.h"
#include "..\Component\Renderer.h"

class DirectionalLight : public GameObject{

public:
	DirectionalLight();
	DirectionalLight(char* name);
	~DirectionalLight();

	virtual bool Initialize();
	virtual void Shutdown();

	XMMATRIX GenerateViewMatrix();
	XMMATRIX GenerateProjectionMatrix(float, float);

private:
	Transform* m_transform;
	ModelMesh* m_mesh;
	Renderer* m_renderer;
	Light* m_light;
};

#endif // !_DIRECTIONAL_LIGHT
