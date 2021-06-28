#pragma once
#include <windows.h>

HWND W_HND;
int W_WIDTH = 110;
int W_HEIGHT = 27;
int TXTAREA_WIDTH = 108;

void setTitle(char str[]) {
	SetConsoleTitle(str);
}

void getHandle() {
	W_HND = GetConsoleWindow();
}

/*
void setWindowSize(int w, int h) {
	SMALL_RECT r = { 0, 0, w, h };
	SetConsoleWindowInfo(W_HND, TRUE, &r);
	
	//RECT r;
	//GetWindowRect(W_HND, &r);
	//MoveWindow(W_HND, r.left, r.right, w, h, TRUE);
	if (1) {}
}
*/