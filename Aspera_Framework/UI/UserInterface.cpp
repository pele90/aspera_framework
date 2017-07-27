#include "UserInterface.h"

UserInterface::UserInterface()
{
	m_font1 = 0;
	m_fpsString = 0;
	m_miniMap = 0;
	m_videoStrings = 0;
	m_renderCountStrings = 0;
	m_renderTimeString = 0;
}

UserInterface::UserInterface(const UserInterface& other){}

UserInterface::~UserInterface(){}

bool UserInterface::Initialize(D3D* Direct3D, int screenHeight, int screenWidth)
{
	bool result;
	char videoCard[128];
	int videoMemory;
	char videoString[144];
	char memoryString[32];
	char tempString[16];

	// Create the first font object.
	m_font1 = new Font;
	if (!m_font1)
	{
		return false;
	}

	// Initialize the first font object.
	result = m_font1->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), "../Aspera_Framework/data/font/font01.txt", 
								 "../Aspera_Framework/data/font/font01.tga", 32.0f, 3);
	if (!result)
	{
		return false;
	}

	// Create the text object for the fps string.
	m_fpsString = new Text;
	if (!m_fpsString)
	{
		return false;
	}

	// Initialize the fps text string.
	result = m_fpsString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_font1, 
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
	m_videoStrings = new Text[2];
	if (!m_videoStrings)
	{
		return false;
	}

	// Initialize the video text strings.
	result = m_videoStrings[0].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 256, false, m_font1, 
										  videoString, 10, 10, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	result = m_videoStrings[1].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_font1, 
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

	// Create the text objects for the render count strings.
	m_renderCountStrings = new Text[3];
	if (!m_renderCountStrings)
	{
		return false;
	}

	// Initialize the render count strings.
	result = m_renderCountStrings[0].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_font1,
		"Polys Drawn: 0", 10, 260, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	result = m_renderCountStrings[1].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_font1,
		"Cells Drawn: 0", 10, 280, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	result = m_renderCountStrings[2].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_font1,
		"Cells Culled: 0", 10, 300, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	m_renderTimeString = new Text;
	if (!m_renderTimeString)
		return false;

	result = m_renderTimeString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_font1,
		"Render time: 0", 10, 320, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}

void UserInterface::Shutdown()
{
	// Release the render time string.
	if (m_renderTimeString)
	{
		m_renderTimeString->Shutdown();
		delete m_renderTimeString;
		m_renderTimeString = 0;
	}

	// Release the render count strings.
	if (m_renderCountStrings)
	{
		m_renderCountStrings[0].Shutdown();
		m_renderCountStrings[1].Shutdown();
		m_renderCountStrings[2].Shutdown();

		delete[] m_renderCountStrings;
		m_renderCountStrings = 0;
	}

	// Release the video card string.
	if(m_videoStrings)
	{
		m_videoStrings[0].Shutdown();
		m_videoStrings[1].Shutdown();

		delete [] m_videoStrings;
		m_videoStrings = 0;
	}

	// Release the mini-map object.
	if (m_miniMap)
	{
		m_miniMap->Shutdown();
		delete m_miniMap;
		m_miniMap = 0;
	}

	// Release the fps text string.
	if(m_fpsString)
	{
		m_fpsString->Shutdown();
		delete m_fpsString;
		m_fpsString = 0;
	}

	// Release the font object.
	if(m_font1)
	{
		m_font1->Shutdown();
		delete m_font1;
		m_font1 = 0;
	}

	return;
}

bool UserInterface::Frame(ID3D11DeviceContext* deviceContext, int fps, XMFLOAT3 position)
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

bool UserInterface::Render(D3D* Direct3D, ShaderManager* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix, 
								XMMATRIX orthoMatrix)
{
	bool result;

	// Turn off the Z buffer and enable alpha blending to begin 2D rendering.
	Direct3D->TurnZBufferOff();
	Direct3D->EnableAlphaBlending();

	// Render the fps string.
	m_fpsString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_font1->GetTexture());

	// Render the video card strings.
	m_videoStrings[0].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_font1->GetTexture());
	m_videoStrings[1].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_font1->GetTexture());

	// Render the render count strings.
	for (int i = 0; i<3; i++)
	{
		m_renderCountStrings[i].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_font1->GetTexture());
	}

	// Render elapsed time of rendering
	m_renderTimeString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_font1->GetTexture());

	// Turn off alpha blending now that the text has been rendered.
	Direct3D->DisableAlphaBlending();

	// Render the mini-map.
	result = m_miniMap->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that the 2D rendering has completed.
	Direct3D->TurnZBufferOn();

	return true;
}

bool UserInterface::UpdateFpsString(ID3D11DeviceContext* deviceContext, int fps)
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
	result = m_fpsString->UpdateSentence(deviceContext, m_font1, finalString, 10, 50, red, green, blue);
	if(!result)
	{
		return false;
	}

	return true;
}

bool UserInterface::UpdateRenderCounts(ID3D11DeviceContext* deviceContext, int renderCount, int nodesDrawn, int nodesCulled)
{
	char tempString[32];
	char finalString[32];
	bool result;


	// Convert the render count integer to string format.
	_itoa_s(renderCount, tempString, 10);

	// Setup the render count string.
	strcpy_s(finalString, "Polys Drawn: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_renderCountStrings[0].UpdateSentence(deviceContext, m_font1, finalString, 10, 260, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Convert the cells drawn integer to string format.
	_itoa_s(nodesDrawn, tempString, 10);

	// Setup the cells drawn string.
	strcpy_s(finalString, "Cells Drawn: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_renderCountStrings[1].UpdateSentence(deviceContext, m_font1, finalString, 10, 280, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Convert the cells culled integer to string format.
	_itoa_s(nodesCulled, tempString, 10);

	// Setup the cells culled string.
	strcpy_s(finalString, "Cells Culled: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_renderCountStrings[2].UpdateSentence(deviceContext, m_font1, finalString, 10, 300, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}

bool UserInterface::UpdateRenderTime(ID3D11DeviceContext* deviceContext, float elapsedTime)
{
	char tempString[32];
	char finalString[32];
	bool result;

	// Convert the render count integer to string format.
	_itoa_s(elapsedTime, tempString, 10);

	// Setup the render count string.
	strcpy_s(finalString, "Render time: ");
	strcat_s(finalString, tempString);
	strcat_s(finalString, " ms");

	// Update the sentence vertex buffer with the new string information.
	result = m_renderTimeString->UpdateSentence(deviceContext, m_font1, finalString, 10, 320, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}