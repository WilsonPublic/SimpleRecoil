struct {
	bool recoil = false;
	int weapon_idx = 0;
} settings;

const char *current_window_title()
{
	char wnd_title[512];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}