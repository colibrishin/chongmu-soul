#pragma once
#include "../control/cwindow.h"
#include <stdio.h>

// TODO : https://www.google.com/search?client=firefox-b-ab&ei=Ct0lW6r6G4Sl8AWvuKvABw&q=console+change+cursor+windows&oq=console+change+cursor+windows&gs_l=psy-ab.3...10317.14178.0.14893.10.10.0.0.0.0.250.1569.0j8j1.9.0....0...1.1.64.psy-ab..1.2.376...0i13k1j0i8i7i30k1.0.Cxhb75Oy7ME
 /*
int scanfBacktab(const char str[], char* c) {
	char* t_str = NULL;
	
	if (sizeof(str) < TXTAREA_WIDTH) {
		t_str = (char*)malloc(getTextPosition(sizeof(str)));
		memset(t_str, '\b', sizeof(t_str));
		t_str[0] = '%';
		t_str[1] = 'c';
		t_str[sizeof(t_str) - 1] = '\0';
	}

	c = getchar();
	free(t_str);
	return TRUE;
}
*/