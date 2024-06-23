#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

void ocultarCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;  // Tamaño del cursor
    cursorInfo.bVisible = FALSE;  // Ocultar el cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void mostrarCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;  // Tamaño del cursor
    cursorInfo.bVisible = true;  // Ocultar el cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void seleccionarOpciones(int &opcion, char &tecla){
	tecla = _getch();
    		
    if(tecla == 72){
		opcion = (opcion - 1 + 6) % 6;
	}else if(tecla == 80){
		opcion = (opcion + 1) % 6;
	}
}