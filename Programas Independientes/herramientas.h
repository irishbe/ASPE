#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

void ocultarCursor();
void mostrarCursor();

void gotoxy(int x, int y){
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

void pantallaDeCarga(int x, int y){
	gotoxy(x, y);   cout<<"\n                     █████";
	gotoxy(x, y+1); cout<<"\n             ▒▒▒▒   ███████   ▒▒▒▒";
	gotoxy(x, y+2); cout<<"\n            ▒▒▒▒▒▒▒  █████  ▒▒▒▒▒▒▒";
	gotoxy(x, y+3); cout<<"\n             ▒▒▒▒▒▒▒▒    ▒▒▒▒▒▒▒▒            ░█████╗░░██████╗██████╗░███████╗";
	gotoxy(x, y+4); cout<<"\n                ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒              ██╔══██╗██╔════╝██╔══██╗██╔════╝";
	gotoxy(x, y+5); cout<<"\n                  ▒▒▒▒▒▒▒▒▒▒▒                ███████║╚█████╗░██████╔╝█████╗░░";
	gotoxy(x, y+6); cout<<"\n                  ▒▒▒▒▒▒▒▒▓▓▒                ██╔══██║░╚═══██╗██╔═══╝░██╔══╝░░";
	gotoxy(x, y+7); cout<<"\n                ▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓              ██║░░██║██████╔╝██║░░░░░███████╗";
	gotoxy(x, y+8); cout<<"\n              ▒▒▒▒▒▒▒▒▒   ▓▓▓▓▓▓▓▓           ╚═╝░░╚═╝╚═════╝░╚═╝░░░░░╚══════╝";
	gotoxy(x, y+9); cout<<"\n             ▒▒▒▒▒▒▒        ▒▓▓▓▓▓▓▓";
	gotoxy(x, y+10);cout<<"\n              ▒▒▒▒             ▓▓▓▓";
}

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

int opcionSelecGotoxy(string textoOpciones[], int numeroOpciones, int x, int y){
	int opcionSeleccionada = 0;
	char tecla;
	
	ocultarCursor();
	//72: Tecla de arriba, 80: Tecla abajo, 13: Enter
	
	do{
		//Mostrando opciones del menu
		for(int i=0; i < numeroOpciones; i++){
			
			if( i != numeroOpciones ){
				gotoxy(x+40,y+5+i);
			}else{
				gotoxy(x+40,y+5+i);
			}
			
			if(opcionSeleccionada == i){
				colorTextoFondo(textoOpciones[i], blancoBrillante, aguamarina);
			}else{
				cout<<textoOpciones[i];
			}
		}
		
		pantallaDeCarga(x,y);
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

void tamanioFuente(int ancho, int alto) {
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return;
    }

    // Configurar la estructura de la fuente
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = ancho;  // Ancho de la fuente
    cfi.dwFontSize.Y = alto;   // Alto de la fuente
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");  // Nombre de la fuente

    // Cambiar el tamaño de la fuente
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void maximizarVentanaConsola() {
    // Obtener el handle de la consola
    HWND hConsole = GetConsoleWindow();
    if (hConsole == nullptr) {
        return;
    }

    // Maximizar la ventana de la consola
    ShowWindow(hConsole, SW_MAXIMIZE);
}