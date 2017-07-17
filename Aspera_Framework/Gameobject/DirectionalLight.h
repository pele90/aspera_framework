#ifndef _DIRECTIONAL_LIGHT
#define _DIRECTIONAL_LIGHT

#include "..\Component\Transform.h"
#include "..\Component\Light.h"
#include "..\Base\GameObject.h"

class DirectionalLight : public GameObject{

public:
	DirectionalLight();
	~DirectionalLight();

	virtual bool Initialize();
	/*bool Initialize();*/
	virtual void Shutdown();

	XMMATRIX GenerateViewMatrix();
	XMMATRIX GenerateProjectionMatrix(float, float);

private:
	Transform* m_transform;
	Light* m_light;
};

#endif // !_DIRECTIONAL_LIGHT
