#include <Windows.h>
#include <stdio.h>

int screenWidth = 120, screenHeight = 30;
int gameFieldWidth = 40, gameFieldHeight = 20;




void write_color(HANDLE buffer, COORD coord, const wchar_t* screen, SHORT length, WORD color)
{
	DWORD written;
	::FillConsoleOutputAttribute(buffer, color, length, coord, &written);
	::WriteConsoleOutputCharacter(buffer, screen, length, coord, &written);
}

void change_color(HANDLE buffer, COORD coord, SHORT length, WORD color)
{
	DWORD written;
	::FillConsoleOutputAttribute(buffer, color, length, coord, &written);
}

int next_buffer_index(int current_buffer_index) {
	if (current_buffer_index == 0) {
		return 1;
	}
	return 0;
}

void strobe() {
	int current_buffer_index = 0;
	HANDLE buffers[2] = {
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) };

	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	screen[screenWidth * screenHeight - 1] = L'\0';
	for (int i = 0; i < screenWidth * screenHeight - 1; i++) {
		screen[i - 1] = L' ';
	}
	int* gameField = new int[gameFieldWidth * gameFieldHeight];
	for (int y = 0; y < gameFieldHeight - 2; y++)
		for (int x = 0; x < gameFieldWidth; x++) {
			screen[screenWidth * (y + 2) + (x + 4)] = L'#';
		}

	bool still_playing = true;
	while (still_playing) {

		write_color(buffers[current_buffer_index], { 0,0 }, screen, screenWidth * screenHeight, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		SHORT offsetx = 4, offsety = 2;
		for (SHORT y = 0; y < gameFieldHeight - 2; y++)
			for (SHORT x = 0; x < gameFieldWidth; x++) {
				COORD coord;
				coord.X = (x + offsetx);
				coord.Y = (y + offsety);
				change_color(buffers[current_buffer_index], coord, 1, BACKGROUND_RED | FOREGROUND_RED);
			}
		SetConsoleActiveScreenBuffer(buffers[current_buffer_index]);
		current_buffer_index = next_buffer_index(current_buffer_index);
		Sleep(1000 / 60);
		write_color(buffers[current_buffer_index], { 0,0 }, screen, screenWidth * screenHeight, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

		for (SHORT y = 0; y < gameFieldHeight - 2; y++)
			for (SHORT x = 0; x < gameFieldWidth; x++) {
				COORD coord;
				coord.X = (x + offsetx);
				coord.Y = (y + offsety);
				change_color(buffers[current_buffer_index], coord, 1, BACKGROUND_GREEN | FOREGROUND_GREEN);
			}
		SetConsoleActiveScreenBuffer(buffers[current_buffer_index]);
		Sleep(1000 / 60);
		SetConsoleActiveScreenBuffer(buffers[current_buffer_index]);
		current_buffer_index = next_buffer_index(current_buffer_index);
	}
}

WORD int_to_background_color(int i) {
	switch (i) {
	case 1: return BACKGROUND_RED; break;
	case 2: return BACKGROUND_RED | BACKGROUND_INTENSITY; break;
	case 3: return BACKGROUND_RED | BACKGROUND_GREEN; break;
	case 4: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
	case 5: return BACKGROUND_GREEN ; break;
	case 6: return BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
	case 7: return BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	case 8: return BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
	case 9: return BACKGROUND_BLUE; break;
	case 10: return BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
	case 11: return BACKGROUND_BLUE | BACKGROUND_RED; break;
	case 12: return BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
	}
	return 0;
}
WORD int_to_foreground_color(int i) {
	switch (i) {
	case 1: return FOREGROUND_RED; break;
	case 2: return FOREGROUND_RED | FOREGROUND_INTENSITY; break;
	case 3: return FOREGROUND_RED | FOREGROUND_GREEN; break;
	case 4: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
	case 5: return FOREGROUND_GREEN; break;
	case 6: return FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
	case 7: return FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	case 8: return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
	case 9: return FOREGROUND_BLUE; break;
	case 10: return FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
	case 11: return FOREGROUND_BLUE | FOREGROUND_RED; break;
	case 12: return FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
	}
	return 0;
}

void rainbow() {
	int current_buffer_index = 0;
	HANDLE buffers[2] = {
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) };

	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	screen[screenWidth * screenHeight - 1] = L'\0';
	for (int i = 0; i < screenWidth * screenHeight - 1; i++) {
		screen[i] = L' ';
	}

	int* color_screen = new int[screenWidth * screenHeight];
	for (int y = 0; y < screenHeight; y++)
		for (int x = 0; x < screenWidth; x++) {
			color_screen[y * screenWidth + x] = (x + y) % 12;
		}
	SHORT offset = 0;
	bool still_running = true;

	while (still_running) {
		for (SHORT y = 0; y < screenHeight; y++)
			for (SHORT x = 0; x < screenWidth; x++) {
				write_color(buffers[current_buffer_index], { x,y }, screen, 1,
					int_to_background_color((color_screen[y * screenWidth + x] + offset) % 12));
			}
		SetConsoleActiveScreenBuffer(buffers[current_buffer_index]);
		current_buffer_index = next_buffer_index(current_buffer_index);
		//Sleep(1000 / 60);
		offset++;
	}
}
void rainbow_static_frames() {
	HANDLE buffers[12] = {
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) };

	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	screen[screenWidth * screenHeight - 1] = L'\0';
	for (int i = 0; i < screenWidth * screenHeight - 1; i++) {
		screen[i] = L' ';
	}

	int* color_screen = new int[screenWidth * screenHeight];
	for (int y = 0; y < screenHeight; y++)
		for (int x = 0; x < screenWidth; x++) {
			color_screen[y * screenWidth + x] = (x + y) % 12;
		}
	SHORT offset = 0;
	bool still_running = true;

	for (int i = 0; i < 12; i++) {
		for (SHORT y = 0; y < screenHeight; y++)
			for (SHORT x = 0; x < screenWidth; x++) {
				write_color(buffers[i], { x,y }, screen, 1,
					int_to_background_color((color_screen[y * screenWidth + x] + offset) % 12));
			}
		offset++;
	}
	while (still_running) {
		for (offset = 0; offset < 12; offset++)
			{
			SetConsoleActiveScreenBuffer(buffers[offset]);
			Sleep(1000 / 120);
			offset++;
			}
	}
}

int main() {
	rainbow_static_frames();
}