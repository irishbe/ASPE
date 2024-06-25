#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

void ocultarCursor();
void mostrarCursor();

enum colores {
	negro = 0,
	azul,
	verde,
	aguamarina,
	rojo,
	purpura,
	amarillo,
	blanco, //gris claro
	gris,
	azulClaro,
	verdeClaro,
	aguamarinaClaro,
	rojoClaro,
	purpuraClaro,
	amarilloClaro,
	blancoBrillante
};
string texto;

// Función para establecer el color del texto
void colorTexto(string texto, colores color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
	cout << texto;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(blanco));
}

// Función para establecer el color del texto y del fondo
void colorTextoFondo(string texto, colores textoColor, colores fondoColor) {
	// Combinar el color del texto y el fondo en un solo atributo
	int atributoColor = static_cast<int>(textoColor) + static_cast<int>(fondoColor) * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), atributoColor);
	cout << texto;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blanco);
}

int opcionSeleccionada(string textoOpciones[], string titulo, int numeroOpciones){
	int opcionSeleccionada = 0;
	char tecla;
	
	ocultarCursor();
	//72: Tecla de arriba, 80: Tecla abajo, 13: Enter
	
	do{
		//Mostrando el titulo
		cout << "\n\n\t"; colorTexto(titulo, blancoBrillante); cout << "\n";
		
		//Mostrando opciones del menu
		for(int i=0; i < numeroOpciones; i++){
			cout << "\n\t";
			if(opcionSeleccionada == i){
				colorTextoFondo(textoOpciones[i], blancoBrillante, aguamarina);
			}else{
				cout<<textoOpciones[i];
			}
		}
		
		tecla = _getch();
		
		if(tecla == 72){
			opcionSeleccionada = (opcionSeleccionada - 1 + numeroOpciones) % numeroOpciones;
		}else if(tecla == 80){
			opcionSeleccionada = (opcionSeleccionada + 1) % numeroOpciones;
		}else if(tecla == 27){
			opcionSeleccionada = numeroOpciones-1; system("cls"); break;
		}
		system("cls");
	}while(tecla != 13);
	
	//Ajustar con el switch que va de 0 a n opciones
	opcionSeleccionada = (opcionSeleccionada + 1) % numeroOpciones;
	
	mostrarCursor();
	return opcionSeleccionada;
}

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