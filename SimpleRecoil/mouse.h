class mouse {
public:
	void move(short x, short y);
	void move_si(short x, short y, short screen_size_x = 1920, short screen_size_y = 1080);
	void set_pointer_pos(short x, short y);
	void click(short delay_ms = 1);
};