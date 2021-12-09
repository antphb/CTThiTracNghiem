#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<conio.h>
using namespace std;
void gotoxy(short x,short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x,y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
//to mau BG
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

int wherey()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
//to mau
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

// man hinh loading
void manHinhLoading()
{
	system("cls");

	gotoxy(75,18);cout << "LOADING...";
	for( int i = 0 ; i <= 50 ; i++ ){
		textcolor(9);
		gotoxy(53 + i,19);cout << char(219);
		textcolor(3);
		gotoxy(77,20);cout << i * 2 << "%";
			Sleep(30);
		}
}
// tao khung hinh
void KhungHinh( int x , int y , int w ){
	gotoxy(x,y);
	SetBGColor(10);
	for(int i = 0 ; i < w ; i++ ){
		if( i == 0 ){
			cout << char(218);
		}
		else if( i == w - 1 ){
			cout << char(191);
		}
		else{
			cout << char(196);
		}
	}
	gotoxy(x,y + 1);
	cout << char(179);
	gotoxy(x + w - 1,y + 1);
	cout << char(179);
	gotoxy(x,y + 2);
	for( int i = 0 ; i < w ; i++ ){
		if( i == 0 ){
			cout << char(192);
		}
		else if( i == w - 1 ){
			cout << char(217);
		}
		else{
			cout << char(196);
		}
	}
	gotoxy(x + 1,y + 1);
}

int wherex()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

//Ham thay doi kich co cua khung console voi tham so truyen vao la chieu cao, chieu rong.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
