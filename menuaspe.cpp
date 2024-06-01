#include <iostream>
#include <cstdlib>  
#include <conio.h>  
#include <windows.h>

using namespace std;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mostrarMenu() {
    system("cls");  
    
    // Centrar el menú
    int menuX = 35; // Ajustar según el ancho de la consola
    int menuY = 5;  // Ajustar según la altura de la consola

    gotoxy(menuX, menuY); cout << "ASPE";
    gotoxy(menuX, menuY + 1); cout << "Usuario: [Nombre]";
    gotoxy(menuX, menuY + 3); cout << "1. Gestor de tareas pendientes";
    gotoxy(menuX, menuY + 4); cout << "2. Administrador de flashcards";
    gotoxy(menuX, menuY + 5); cout << "3. Registro de calificaciones";
    gotoxy(menuX, menuY + 6); cout << "4. Terminar periodo academico";
    gotoxy(menuX, menuY + 7); cout << "5. Renombrar periodo academico";
    gotoxy(menuX, menuY + 8); cout << "0. SALIR";
}

int main() {
    // Centrar el mensaje de bienvenida
    int welcomeX = 30; // Ajustar según el ancho de la consola
    int welcomeY = 10; // Ajustar según la altura de la consola

    gotoxy(welcomeX, welcomeY); cout << "ASPE";
    gotoxy(welcomeX, welcomeY + 1); cout << "Bienvenido a la Aplicacion de Seguimiento del Progreso Estudiantil (ASPE)";
    
   
    gotoxy(welcomeX, welcomeY + 3); cout << "Presione cualquier tecla para continuar...";
    _getch();  
    
    
    mostrarMenu();
    
    
    int opcion;
    gotoxy(35, 15); // Ajustar la posición del cursor para la entrada
    cin >> opcion;
    
    return 0;
}