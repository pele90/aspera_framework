#include "userinterfaceclass.h"

UserInterfaceClass::UserInterfaceClass()
{
	m_Font1 = 0;
	m_FpsString = 0;
	m_miniMap = 0;
	m_VideoStrings = 0;
}

UserInterfaceClass::UserInterfaceClass(const UserInterfaceClass& other)
{
}

UserInterfaceClass::~UserInterfaceClass()
{
}

bool UserInterfaceClass::Initialize(D3D* Direct3D, int screenHeight, int screenWidth)
{
	bool result;
	char videoCard[128];
	int videoMemory;
	char videoString[144];
	char memoryString[32];
	char tempString[16];
	int i;


	// Create the first font object.
	m_Font1 = new FontClass;
	if (!m_Font1)
	{
		return false;
	}

	// Initialize the first font object.
	result = m_Font1->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), "../Aspera_Framework/data/font/font01.txt", 
								 "../Aspera_Framework/data/font/font01.tga", 32.0f, 3);
	if (!result)
	{
		return false;
	}

	// Create the text object for the fps string.
	m_FpsString = new TextClass;
	if (!m_FpsString)
	{
		return false;
	}

	// Initialize the fps text string.
	result = m_FpsString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
									 "Fps: 0", 10, 50, 0.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Initial the previous frame fps.
	m_previousFps = -1;

	// Setup the video card strings.
	Direct3D->GetVideoCardInfo(videoCard, videoMemory);
	strcpy_s(videoString, "Video Card: ");
	strcat_s(videoString, videoCard);

	_itoa_s(videoMemory, tempString, 10);

	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");

	// Create the text objects for the video strings.
	m_VideoStrings = new TextClass[2];
	if (!m_VideoStrings)
	{
		return false;
	}

	// Initialize the video text strings.
	result = m_VideoStrings[0].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 256, false, m_Font1, 
										  videoString, 10, 10, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	result = m_VideoStrings[1].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1, 
										  memoryString, 10, 30, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false;
	}

	// Create the mini-map object.
	m_miniMap = new MiniMap;
	if (!m_miniMap)
	{
		return false;
	}

	// Initialize the mini-map object.
	result = m_miniMap->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 1025, 1025);
	if (!m_miniMap)
	{
		return false;
	}

	return true;
}

void UserInterfaceClass::Shutdown()
{
	// Release the video card string.
	if(m_VideoStrings)
	{
		m_VideoStrings[0].Shutdown();
		m_VideoStrings[1].Shutdown();

		delete [] m_VideoStrings;
		m_VideoStrings = 0;
	}

	// Release the mini-map object.
	if (m_miniMap)
	{
		m_miniMap->Shutdown();
		delete m_miniMap;
		m_miniMap = 0;
	}

	// Release the fps text string.
	if(m_FpsString)
	{
		m_FpsString->Shutdown();
		delete m_FpsString;
		m_FpsString = 0;
	}

	// Release the font object.
	if(m_Font1)
	{
		m_Font1->Shutdown();
		delete m_Font1;
		m_Font1 = 0;
	}

	return;
}

bool UserInterfaceClass::Frame(ID3D11DeviceContext* deviceContext, int fps, XMFLOAT3 position)
{
	bool result;

	// Update the fps string.
	result = UpdateFpsString(deviceContext, fps);
	if(!result)
	{
		return false;
	}

	// Update the mini-map position indicator.
	m_miniMap->PositionUpdate(position.x, position.z);

	return true;
}

bool UserInterfaceClass::Render(D3D* Direct3D, ShaderManager* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix, 
								XMMATRIX orthoMatrix)
{
	int i;
	bool result;

	// Turn off the Z buffer and enable alpha blending to begin 2D rendering.
	Direct3D->TurnZBufferOff();
	Direct3D->EnableAlphaBlending();

	// Render the fps string.
	m_FpsString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());

	// Render the video card strings.
	m_VideoStrings[0].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	m_VideoStrings[1].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());

	// Turn off alpha blending now that the text has been rendered.
	Direct3D->DisableAlphaBlending();

	// Render the mini-map.
	/*result = m_miniMap->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}*/

	// Turn the Z buffer back on now that the 2D rendering has completed.
	Direct3D->TurnZBufferOn();

	return true;
}

bool UserInterfaceClass::UpdateFpsString(ID3D11DeviceContext* deviceContext, int fps)
{
	char tempString[16];
	char finalString[16];
	float red, green, blue;
	bool result;


	// Check if the fps from the previous frame was the same, if so don't need to update the text string.
	if(m_previousFps == fps)
	{
		return true;
	}

	// Store the fps for checking next frame.
	m_previousFps = fps;

	// Truncate the fps to below 100,000.
	if(fps > 99999)
	{
		fps = 99999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(finalString, "Fps: ");
	strcat_s(finalString, tempString);

	// If fps is 60 or above set the fps color to green.
	if(fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if(fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if(fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = m_FpsString->UpdateSentence(deviceContext, m_Font1, finalString, 10, 50, red, green, blue);
	if(!result)
	{
		return false;
	}

	return true;
}