#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include "../Graphics/Text.h"
#include "../Graphics/MiniMap.h"

class UserInterface
{
public:
	UserInterface();
	UserInterface(const UserInterface&);
	~UserInterface();

	bool Initialize(D3D*, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int, XMFLOAT3);
	bool Render(D3D*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX);

	bool UpdateRenderCounts(ID3D11DeviceContext*, int, int, int);
	bool UpdateRenderTime(ID3D11DeviceContext*, float);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);

private:
	Font* m_font1;
	Text* m_fpsString;
	Text* m_videoStrings;
	Text* m_renderCountStrings;
	Text* m_renderTimeString;
	int m_previousFps;
	MiniMap* m_miniMap;
	//int m_previousPosition[6];
};

#endif "!_USER_INTERFACE_H_"