#ifndef _MESSAGE_ALERT_H_
#define _MESSAGE_ALERT_H_

#include <windows.h>

class MessageAlert
{
public:
	MessageAlert();
	MessageAlert(const MessageAlert&);
	~MessageAlert();

	void Initialize(HWND hwnd);
	void Shutdown();

	void ShowMessage(LPCWSTR content, LPCWSTR title);

private:
	HWND m_hwnd;
};

#endif // !_MESSAGE_ALERT_H_

