#pragma once
//
//
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
std::mutex m;
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
	static void GameField(const int x_length, const int y_length, const char sym_leftright_part, const char sym_downbot_part) {
		for (int i = 0; i < x_length; i++) // y = 0
			std::cout << sym_downbot_part;
		std::cout << "\n";
		for (int y = 0; y < (y_length-2); y++) {
			for (int x = 0; x < x_length; x++) {
				if ( x == 0 || x == (x_length - 1) )
					std::cout << sym_leftright_part;
				else 
					std::cout << ' ';
			}
			std::cout << "\n";
		}
		for (int i = 0; i < x_length; i++)  // y = y_length
			std::cout << sym_downbot_part;
		std::cout << "\n";
	}
	//
	static void VolumeObject(int x_position, int y_position, const int x_length, const int y_length, const char sym) {
		int start_x_position = x_position;
		for (int y = 0; y < y_length; y++) {
			for ( int x = 0; x < x_length; x++)
			{
				Object(x_position, y_position, sym);
				x_position++;
			}
			x_position = start_x_position;
			y_position++;
		}
	}
	//
	template<typename type> static void VolumeObjectArr(int x_position, int y_position, const type &arrayObject) {
		int start_x_position = x_position;
		for (int i = 0; i < 5; i++) {
			for (int y = 0; y < 36; y++) {
				Object(x_position, y_position, arrayObject[i][y]);
				x_position++;
			}
			x_position = start_x_position;
			y_position++;
		}
	}
	//
	static void Object(const int x, const int y, const char sym) {
		std::lock_guard<std::mutex> lock(m);
	 	COORD position = { x, y };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		std::cout << sym;
	}
	//
	static void Clear(const int x, const int y) {
		std::lock_guard<std::mutex> lock(m);
		COORD position = { x, y };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		std::cout << " ";
	}
};
#endif