#pragma once

#include "Base.h"

BEGIN(Engine)

class CInput_Device final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)

	struct tKeyInfo {
		KEY_STATE eState;
		bool bPrevPush; // ���� ������ üũ �뵵
	};

public:

	_byte Get_DIMouseKeyState(MOUSEBUTTON eMouseButtonID) {
		return m_MouseState.rgbButtons[(_uint)eMouseButtonID];
	}

	_long Get_DIMouseMoveState(MOUSEMOVE eMouseMove) {
		return *((_long*)&m_MouseState + (_uint)eMouseMove);
	}

	const vector<tKeyInfo>& Get_vecKey() { return m_vecKey; }

	KEY_STATE				Get_KeyState(KEY _key);

public:
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);
	HRESULT SetUp_DeviceState();

	HRESULT Tick();

private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse = nullptr;

private:
	DIMOUSESTATE			m_MouseState;
	HWND					m_Handle;
	vector<tKeyInfo>		m_vecKey; // ���� ���� �ε����� �� Ű ���� �ǹ���


public:
	void Free();
};

END