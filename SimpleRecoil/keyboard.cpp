#include <windows.h>
#include <thread>
#include "keyboard.h"

void keyboard::key_press(int vkey, int delay_ms) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vkey;
	SendInput(1, &input, sizeof(INPUT)); //pressing key
	std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
	input.ki.dwFlags = KEYEVENTF_KEYUP; 
	SendInput(1, &input, sizeof(INPUT)); //releasing key
}