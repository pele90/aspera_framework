#ifndef _CAMERA_MOVEMENT_SYSTEM_H_
#define _CAMERA_MOVEMENT_SYSTEM_H_

#include <DirectXMath.h>
#include "../Base/GameObject.h"
#include "../MISC/InputClass.h"
#include "../Component/Transform.h"

using namespace DirectX;

class CameraMovementSystem
{
public:
	CameraMovementSystem();
	~CameraMovementSystem();

	bool Initialize();
	void Shutdown();

	void HandleMovementInput(InputClass*, GameObject*, int);

private:
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);
	void StrafeLeft(bool);
	void StrafeRight(bool);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;
	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
	float m_strafeLeftSpeed, m_strafeRightSpeed;
	float m_camPitch, m_camYaw;

};

#endif // !_CAMERA_MOVEMENT_SYSTEM_H_

