#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include <directxmath.h>
using namespace DirectX;

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	virtual bool Initialize();
	virtual void Shutdown();

	void RenderViewMatrix();
	void GetViewMatrix(XMMATRIX&);
	void RenderBaseViewMatrix();
	void GetBaseViewMatrix(XMMATRIX&);

private:
	Transform* m_Transform;
	XMMATRIX m_viewMatrix, m_baseViewMatrix;
	XMVECTOR m_lookAtVector;

};

#endif _CAMERA_H_