#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <locale>
#include <stdlib.h>
#include <random>

int nx, ny, W, ir, jr, rr, rr1, d1, d2;

void main()
{

	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevConsoleMode = 0;
	GetConsoleMode(hConsole, &prevConsoleMode);
	SetConsoleMode(hConsole, prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE);
	HWND hwnd = GetConsoleWindow();
	ShowScrollBar(hwnd, SB_VERT, 0);
	EnableScrollBar(hwnd, SB_BOTH, 0);
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &info)) {
		COORD coord;
		coord.X = info.srWindow.Right - info.srWindow.Left + 1;
		coord.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
		SetConsoleScreenBufferSize(hConsoleOutput, coord);
	}
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	setlocale(LC_ALL, "rus");
	std::cout << "Использование горячих клавиш может вызвать некорректную работу программы!\n";
	std::cout << "Введите количество столбцов (от 3 до 15): ";
	std::cin >> nx;
	std::cout << "Введите количество строк (от 3 до 35): ";
	std::cin >> ny;
	std::cout << "Введите размер клеток (от 15 до 25): ";
	std::cin >> W;

	if ((nx >=3) && (nx <=15) && (ny >= 3) && (ny <=35) && (W>=15) && (W<=25))
	{
		system("cls");
		Sleep(1000);
		getchar();

		HDC hdc = GetDC(hwnd);

		HPEN pen = (HPEN)GetStockObject(WHITE_PEN);
		SelectObject(hdc, pen);
		HBRUSH br = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH brold = (HBRUSH)SelectObject(hdc, br);

		for (int i = 1; i <= ny; i++)
		{
			for (int j = 1; j <= nx; j++)
			{
				Rectangle(hdc, i * W, j * W, i * W + W, j * W + W);
			}

		}

		SelectObject(hdc, brold);
		DeleteObject(br);
		HBRUSH br1 = CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH brold1 = (HBRUSH)SelectObject(hdc, br1);
		std::random_device dev;
		std::mt19937 rng(dev());
		while (2 > 1)
		{
			std::uniform_int_distribution<std::mt19937::result_type> i0(1, nx);
			ir = i0(rng);
			std::uniform_int_distribution<std::mt19937::result_type> y0(1, ny);
			jr = y0(rng);
			std::uniform_int_distribution<std::mt19937::result_type> dd2(0, 5);
			d2 = dd2(rng);
			std::uniform_int_distribution<std::mt19937::result_type> r0(1, W - d2);
			rr = r0(rng);
			std::uniform_int_distribution<std::mt19937::result_type> dd1(0, 5);
			d1 = dd1(rng);
			std::uniform_int_distribution<std::mt19937::result_type> r1(1, W - d1);
			rr1 = r1(rng);
			Ellipse(hdc, jr * W + rr1, ir * W + rr1, jr * W + rr, ir * W + rr);
			Sleep(100);
		}

		SelectObject(hdc, brold);
		DeleteObject(br);
		ReleaseDC(hwnd, hdc);
		getchar();
	}
	else
	{
		std::cout << "Неверно введено количество столбцов, строк или размер клетки!";
	}
}
