#include <iostream>
#include <windows.h>

using namespace std;

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