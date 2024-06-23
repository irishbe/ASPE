#include <cstdlib>  
#include <conio.h>

using namespace std;

short i, j, n, id;
extern short i, j, n, id;

// Declaración de la función
#include "Modulos ASPE/GestorDeTareas.h"
#include "Modulos ASPE/SistemaDeFlashcards.h"
#include "Modulos ASPE/PonderadoNotas.h"
#include "Modulos ASPE/herramientas.h"

void mostrarMenu(int opcion) {
    system("cls");  
    
    // Centrar el menú
    int menuX = 40; // Ajustar según el ancho de la consola
    int menuY = 5;  // Ajustar según la altura de la consola

    gotoxy(menuX, menuY); cout << "ASPE";
    gotoxy(menuX, menuY + 1); cout << "Usuario: [Nombre]";
    gotoxy(menuX, menuY + 3); cout << (opcion == 1 ? "-> " : "   ") << "1. Gestor de tareas pendientes";
    gotoxy(menuX, menuY + 4); cout << (opcion == 2 ? "-> " : "   ") << "2. Administrador de flashcards";
    gotoxy(menuX, menuY + 5); cout << (opcion == 3 ? "-> " : "   ") << "3. Registro de calificaciones";
    gotoxy(menuX, menuY + 6); cout << (opcion == 4 ? "-> " : "   ") << "4. Terminar periodo academico";
    gotoxy(menuX, menuY + 7); cout << (opcion == 5 ? "-> " : "   ") << "5. Renombrar periodo academico";
    gotoxy(menuX, menuY + 8); cout << (opcion == 0 ? "-> " : "   ") << "0. SALIR";
}

int main() {
    // Centrar el mensaje de bienvenida
    int welcomeX = 25; // Ajustar según el ancho de la consola
    int welcomeY = 10; // Ajustar según la altura de la consola

    gotoxy(welcomeX, welcomeY); cout << "ASPE";
    gotoxy(welcomeX, welcomeY + 1); cout << "Bienvenido a la Aplicacion de Seguimiento del Progreso Estudiantil (ASPE)";
    
   
    gotoxy(welcomeX, welcomeY + 3); cout << "Presione cualquier tecla para continuar...";
    _getch();  
    
    int opcion = 1;
    char tecla;
    
    do{
    	
    	do{
    		mostrarMenu(opcion);
    		ocultarCursor();
    		seleccionarOpciones(opcion, tecla);
		}while(tecla != 13);
		
		system("cls");
		
		mostrarCursor();
    	switch(opcion){
    		case 1: GestorDeTareas(); break;
    		case 2: SistemaDeFlashcards(); break;
    		case 3: PonderadoNotas(); break;
    		case 0: cout<< "Saliendo.... \n\nGracias por utilizar ASPE!"<<endl; break;
    		default: cout<<"Opcion invalida o aun no disponible "; getch();
		}
    	
	}while(opcion != 0);
    
    return 0;
}