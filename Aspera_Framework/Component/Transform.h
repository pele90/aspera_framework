#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../Base/Component.h"
#include <DirectXMath.h>
using namespace DirectX;

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual bool Initialize();
	virtual void Shutdown();

	void SetTransform(const Transform other);
	void SetTransform(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot);
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Reset();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

};

#endif // !_TRANSFORM_H_

