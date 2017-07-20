#include "CameraMovementSystem.h"

CameraMovementSystem::CameraMovementSystem()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed = 0.0f;
	m_backwardSpeed = 0.0f;
	m_upwardSpeed = 0.0f;
	m_downwardSpeed = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;
	m_camPitch = 0.0f;
	m_camYaw = 0.0f;
}

CameraMovementSystem::~CameraMovementSystem()
{
}

bool CameraMovementSystem::Initialize()
{
	return true;
}

void CameraMovementSystem::Shutdown()
{
}

void CameraMovementSystem::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}

void CameraMovementSystem::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void CameraMovementSystem::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}

void CameraMovementSystem::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}

void CameraMovementSystem::HandleMovementInput(Input* p_input, GameObject* p_gameobject, int p_frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
	float pitch, yaw;
	XMFLOAT3 position, rotation;

	position = p_gameobject->GetComponent<Transform>("TRANSFORM")->GetPosition();

	SetPosition(position.x, position.y, position.z);

	// Set the frame time for calculating the updated position.
	m_frameTime = p_frameTime;

	// Get mouse movement x and y position as pitch and yaw of rotation
	p_input->GetPitchAndYaw(pitch, yaw);

	// Set mouse movement x and y position as pitch and yaw of rotation
	rotation = XMFLOAT3(pitch, yaw, 0.0f);
	SetRotation(rotation.x, rotation.y, rotation.z);

	// Handle the input.
	keyDown = p_input->IsLeftPressed();
	TurnLeft(keyDown);

	keyDown = p_input->IsRightPressed();
	TurnRight(keyDown);

	keyDown = p_input->IsUpPressed();
	MoveUpward(keyDown);

	keyDown = p_input->IsDownPressed();
	MoveDownward(keyDown);

	keyDown = p_input->IsAPressed();
	StrafeLeft(keyDown);

	keyDown = p_input->IsZPressed();
	MoveDownward(keyDown);

	keyDown = p_input->IsQPressed();
	StrafeLeft(keyDown);

	keyDown = p_input->IsEPressed();
	StrafeRight(keyDown);

	keyDown = p_input->IsWPressed();
	MoveForward(keyDown);

	keyDown = p_input->IsSPressed();
	MoveBackward(keyDown);

	keyDown = p_input->IsDPressed();
	StrafeRight(keyDown);

	keyDown = p_input->IsSpacePressed();
	MoveUpward(keyDown);

	// Get the view point position/rotation.
	GetPosition(posX, posY, posZ);
	GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	p_gameobject->GetComponent<Transform>("TRANSFORM")->SetPosition(posX, posY, posZ);
	p_gameobject->GetComponent<Transform>("TRANSFORM")->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if (p_input->IsF1Toggled())
	{
		//m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (p_input->IsF2Toggled())
	{
		//m_wireFrame = !m_wireFrame;
	}
}

void CameraMovementSystem::MoveForward(bool keydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_forwardSpeed += 0.2f;

		if (m_forwardSpeed > 2.0f)
		{
			m_forwardSpeed = 2.0f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	float radius = m_forwardSpeed;
	float yaw = m_rotationY * 0.0174532925f;
	float pitch = m_rotationX * 0.0174532925f;

	float xMove = radius * sinf(yaw) * cosf(pitch);
	float yMove = radius * -sinf(pitch);
	float zMove = radius * cosf(yaw) * cosf(pitch);


	m_positionX += xMove;
	m_positionY += yMove;
	m_positionZ += zMove;

	return;
}

void CameraMovementSystem::MoveBackward(bool keydown)
{
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_backwardSpeed += 0.2f;

		if (m_backwardSpeed > 2.0f)
		{
			m_backwardSpeed = 2.0f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.5f;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	float radius = m_backwardSpeed;
	float yaw = m_rotationY * 0.0174532925f;
	float pitch = m_rotationX * 0.0174532925f;

	float xMove = radius * sinf(yaw) * cosf(pitch);
	float yMove = radius * -sinf(pitch);
	float zMove = radius * cosf(yaw) * cosf(pitch);

	m_positionX -= xMove;
	m_positionY -= yMove;
	m_positionZ -= zMove;

	return;
}

void CameraMovementSystem::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_upwardSpeed += m_frameTime * 0.04f;

		if (m_upwardSpeed > (m_frameTime * 0.2f))
		{
			m_upwardSpeed = m_frameTime * 0.2f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.5f;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;

	return;
}

void CameraMovementSystem::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_downwardSpeed += m_frameTime * 0.4f;

		if (m_downwardSpeed > (m_frameTime * 0.5f))
		{
			m_downwardSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.5f;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;

	return;
}

void CameraMovementSystem::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.9f;

		if (m_leftTurnSpeed > (m_frameTime * 0.5f))
		{
			m_leftTurnSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 3.5f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

void CameraMovementSystem::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.9f;

		if (m_rightTurnSpeed > (m_frameTime * 0.5f))
		{
			m_rightTurnSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 3.5f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}

void CameraMovementSystem::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.4f;

		if (m_lookUpSpeed > (m_frameTime * 0.5f))
		{
			m_lookUpSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 2.0f;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

void CameraMovementSystem::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.4f;

		if (m_lookDownSpeed > (m_frameTime * 0.5f))
		{
			m_lookDownSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 2.0f;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

void CameraMovementSystem::StrafeLeft(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_strafeLeftSpeed += m_frameTime * 0.04f;

		if (m_strafeLeftSpeed > (m_frameTime * 0.5f))
		{
			m_strafeLeftSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_strafeLeftSpeed -= m_frameTime * 2.0f;

		if (m_strafeLeftSpeed < 0)
		{
			m_strafeLeftSpeed = 0;
		}
	}

	float radius = m_strafeLeftSpeed;
	float yaw = (m_rotationY + 90) * 0.0174532925f;
	float pitch = m_rotationX * 0.0174532925f;

	float xMove = radius * sinf(yaw) * cosf(pitch);
	float yMove = radius * -sinf(pitch);
	float zMove = radius * cosf(yaw) * cosf(pitch);

	m_positionX -= xMove;
	m_positionY -= yMove;
	m_positionZ -= zMove;

	return;
}

void CameraMovementSystem::StrafeRight(bool keydown)
{
	float radians;

	if (keydown)
	{
		m_strafeRightSpeed += m_frameTime * 0.04f;

		if (m_strafeRightSpeed > (m_frameTime * 0.5f))
		{
			m_strafeRightSpeed = m_frameTime * 0.5f;
		}
	}
	else
	{
		m_strafeRightSpeed -= m_frameTime * 2.0f;

		if (m_strafeRightSpeed < 0)
		{
			m_strafeRightSpeed = 0;
		}
	}

	float radius = m_strafeRightSpeed;
	float yaw = (m_rotationY + 90) * 0.0174532925f;
	float pitch = m_rotationX * 0.0174532925f;

	float xMove = radius * sinf(yaw) * cosf(pitch);
	float yMove = radius * -sinf(pitch);
	float zMove = radius * cosf(yaw) * cosf(pitch);

	m_positionX += xMove;
	m_positionY += yMove;
	m_positionZ += zMove;

	return;
}