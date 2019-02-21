#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<Xinput.h>
#include <thread>
#include <omp.h>

using namespace std;
#pragma comment(lib, "XInput.lib")

int joint1 = 0;
int joint2 = 0;
int joint3 = 0;
int joint4 = 0;
int joint5 = 0;
int joint6 = 0;
int delta = 5;

struct Controller {
	XINPUT_STATE state;
};

class Joypad {
public:
	int getJoystickPort(XINPUT_STATE* state2)
	{
		DWORD dwResult;
		int port = -1;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			dwResult = XInputGetState(i, &state);
			if (dwResult == ERROR_SUCCESS)
			{
				*state2 = state;
				port = i;
				cout << i << " - Porta conectada" << endl;
				cout << "pointer: " << state.Gamepad.wButtons << endl;
			}
			else {
				cout << i << " - Porta desconectada" << endl;
			}
		}
		Sleep(100);
		//system("cls");
		return port;
	}
};

void joystickStates() {
	XINPUT_STATE state;
	Joypad* joypad = new Joypad;
	int button;
	int port;
	while (1) {
		port = joypad->getJoystickPort(&state);
		button = state.Gamepad.wButtons;
		//Sleep(50);
		//cout << "Botao " << state.Gamepad.wButtons << endl;
	}
}

int main() {
	//thread t1(joystickStates());
	//CreateThread();
	//joystickStates();

	#pragma omp parallel sections 
	{
		#pragma omp section
		{
			while (1) {
				cout << "TCP SOCKET HERE" << endl;
			}

		}
		#pragma omp section
		{
			joystickStates();
		}
	}

	return 0;
}