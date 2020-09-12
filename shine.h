#if !defined SHINE_H
#define SHINE_H
//
//
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <mutex> 
//
//
static std::mutex m;
//
class ShineFunction {
public:
	static int FindKey() {
		bool key_find = true;
		std::cout << "Press button" << "\n";
		while (key_find)
		{
			if (_kbhit()) {
				int key = _getch();
				key_find = false;
				return key;
			}
		}
	}
	//
	static void SetConsoleSize(const int x_size, const int y_size) {
		char Title[1024];
		HWND hwnd = GetConsoleWindow();
		MoveWindow(hwnd, 200, 200, x_size, y_size, TRUE);
	}
};
//
class Shine {
public:
	//
	static void SetCursorPosition(const int x_position, const int y_position) {
		COORD position = { x_position, y_position }; 
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
	}
	//
	static void GameField(const int x_length, const int y_length, const char sym) {
		for (int i = 0; i < x_length; i++) // Top part
			std::cout << sym;
		std::cout << '\n';
		for (int y = 0; y < (y_length - 2); y++) { //Middle part
			for (int x = 0; x < x_length; x++) {
				if (x == 0 || x == (x_length - 1))
					std::cout << sym;
				else
					std::cout << ' ';
			}
			std::cout << '\n';
		}
		for (int i = 0; i < x_length; i++)  // Bottom part
			std::cout << sym;
		std::cout << '\n';
	}
	//
	static void GameField(const int x_length, const int y_length, const char sym_leftright_part, const char sym_downbot_part) {
		for (int i = 0; i < x_length; i++) // Top part
			std::cout << sym_downbot_part;
		std::cout << '\n';
		for (int y = 0; y < (y_length-2); y++) { //Middle part
			for (int x = 0; x < x_length; x++) {
				if ( x == 0 || x == (x_length - 1) )
					std::cout << sym_leftright_part;
				else 
					std::cout << ' ';
			}
			std::cout << '\n';
		}
		for (int i = 0; i < x_length; i++)  /// Bottom part
			std::cout << sym_downbot_part;
		std::cout << '\n';
	}
	//
	static void VolumeObject(int x_position, int y_position, const int x_length, const int y_length, const char sym) {
		int start_x_position = x_position;
		for (int y = 0; y < y_length; y++) {
			for ( int x = 0; x < x_length; x++)
			{
				Object(x_position, y_position, sym);
				++x_position;
			}
			x_position = start_x_position;
			++y_position;
		}
	}
	//
	template<typename type> static void VolumeObjectArr(int x_position, int y_position, const type &arrayObject) {
		int start_x_position = x_position;
		for (int i = 0; i < 11; i++) {
			for (int y = 0; y < 16; y++) {
				Object(x_position, y_position, arrayObject[i][y]);
				++x_position;
			}
			x_position = start_x_position;
			++y_position;
		}
	}
	//	
	template<typename type> static void VolumeObjectArr(int x_position, int y_position, const int width, const int height, const type& arrayObject) {
		int start_x_position = x_position;
		for (int i = 0; i < height; i++) {
			for (int y = 0; y < width; y++) {
				Object(x_position, y_position, arrayObject[i][y]);
				++x_position;
			}
			x_position = start_x_position;
			++y_position;
		}
	}
	//
	static void Object(const int x, const int y, const char sym) {
	 	_COORD position = { x, y };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::lock_guard<std::mutex> lock(m);
		SetConsoleCursorPosition(hConsole, position);
		std::cout << sym;
	}
	//
	static void Clear(const int x, const int y) {
		COORD position = { x, y };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::lock_guard<std::mutex> lock(m);
		SetConsoleCursorPosition(hConsole, position);
		std::cout << " ";
	}
};
#endif