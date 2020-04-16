#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include "simple_recoil.h"
#include "mouse.h"
#include "keyboard.h"

void recoil_thread();
void input_thread();

mouse m;
keyboard k;

enum weapon_list {
	weapon1,
	weapon2,
	weapon3
};

struct pattern {
	std::vector<short> x, y;
	int fire_rate;
};

std::vector<pattern> weapon;

void initialize_patterns(std::vector<pattern>& vector, int weapon_count) { 
	for (int i = 0; i < weapon_count; i++)
		vector.push_back(pattern());

	vector[weapon1].x = { 1, 2, 3, 4, 5 }; //replace this array with your weapon's x recoil patterns
	vector[weapon1].y = { 1, 2, 3, 4, 5 }; //replace this array with your weapon's y recoil patterns
	vector[weapon1].fire_rate = 100; //to find the 'fire_rate' of your weapon, find it's rounds per minute and put it into the following calculation (you can use google): 1000 / (rpm / 60)

	vector[weapon2].x = { 2, 4, 6, 8, 10 }; 
	vector[weapon2].y = { 2, 4, 6, 8, 10 };
	vector[weapon2].fire_rate = 50;

	vector[weapon3].x = { 3, 6, 9, 12, 15 };
	vector[weapon3].y = { 3, 6, 9, 12, 15 };
	vector[weapon3].fire_rate = 25;
}

int main(int argc, char *argv[]) {
	enum priority_class {
		realtime = 0x00000100,
		high = 0x00000080,
		above_normal = 0x00008000,
		normal = 0x00000020,
		below_normal = 0x00004000
	};
	SetPriorityClass(GetCurrentProcess(), high); //setting process priority
	initialize_patterns(weapon, 3); //replace 'weapon_count' (3) with how many weapons you are adding, this is to improve memory usage
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)input_thread, NULL, NULL, NULL); //creating 'input_thread' thread for getting key states
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recoil_thread, NULL, NULL, NULL); //creating 'recoil_thread' for the main recoil function

	for (;;)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return NULL;
}

void recoil_thread() {
	for (;;) {
		int counter = 0;
		if (current_window_title() == "Apex Legends") {
			while (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
				if (counter < weapon[settings.weapon_idx].x.size()) {
					for (int i = 0; i < 4; i++) {
						m.move(weapon[settings.weapon_idx].x[counter] / 4, weapon[settings.weapon_idx].y[counter] / 4);
						std::this_thread::sleep_for(std::chrono::milliseconds(weapon[settings.weapon_idx].fire_rate / 4));
					}

					m.move(weapon[settings.weapon_idx].x[counter] % 4, weapon[settings.weapon_idx].y[counter] % 4);
					std::this_thread::sleep_for(std::chrono::milliseconds(weapon[settings.weapon_idx].fire_rate % 4));
					counter++;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void input_thread() {
	for (;;) {
		if (GetAsyncKeyState(VK_F2) & 0x8000) {
			settings.recoil = !settings.recoil;
			Beep(300 + settings.recoil * 200, 200);
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && settings.weapon_idx > 0) {
			settings.weapon_idx--;
			Beep(400, 200);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && settings.weapon_idx < weapon.size() - 1) {
			settings.weapon_idx++;
			Beep(400, 200);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
