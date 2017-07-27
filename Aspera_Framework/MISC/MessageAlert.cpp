#include "..\MISC\MessageAlert.h"

MessageAlert::MessageAlert(){}

MessageAlert::MessageAlert(const MessageAlert &){}

MessageAlert::~MessageAlert(){}

void MessageAlert::Initialize(HWND hwnd)
{
	m_hwnd = hwnd;
}

void MessageAlert::Shutdown(){}

void MessageAlert::ShowMessage(LPCWSTR content, LPCWSTR title)
{
	MessageBox(m_hwnd, content, title, MB_OK);
}


