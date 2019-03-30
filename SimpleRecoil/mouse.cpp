#include <windows.h>
#include <thread>
#include "mouse.h"

void mouse::move(short x, short y) {
	mouse_event(MOUSEEVENTF_MOVE, x, y, NULL, NULL);
}
void mouse::move_si(short x, short y, short screen_size_x, short screen_size_y) {
	double fx = x * (65535.0f / screen_size_x);
	double fy = y * (65535.0f / screen_size_y);
	INPUT Input = { NULL };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1, &Input, sizeof(INPUT));
}
void mouse::set_pointer_pos(short x, short y) {
	SetCursorPos(x, y);
}
void mouse::click(short delay_ms) {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, NULL, NULL);
	std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, NULL, NULL);
}