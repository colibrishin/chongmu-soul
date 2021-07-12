#include "cwindow.h"

void setTitle(char str[]) {
  SetConsoleTitle(str);
}

HWND getHandle() {
  return GetConsoleWindow();
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