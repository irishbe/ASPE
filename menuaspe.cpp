#include <cstdlib>  
#include <conio.h>

using namespace std;

short i, j, n, id;
extern short i, j, n, id;

// Declaración de la función
#include "Modulos ASPE/GestorDeTareas.h"
#include "Modulos ASPE/SistemaDeFlashcards.h"
#include "Modulos ASPE/PonderadoNotas.h"

void mostrarMenu() {
    system("cls");  
    
    // Centrar el menú
    int menuX = 40; // Ajustar según el ancho de la consola
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
    int welcomeX = 25; // Ajustar según el ancho de la consola
    int welcomeY = 10; // Ajustar según la altura de la consola

    gotoxy(welcomeX, welcomeY); cout << "ASPE";
    gotoxy(welcomeX, welcomeY + 1); cout << "Bienvenido a la Aplicacion de Seguimiento del Progreso Estudiantil (ASPE)";
    
   
    gotoxy(welcomeX, welcomeY + 3); cout << "Presione cualquier tecla para continuar...";
    _getch();  
    
    char opcion;
    
    do{
    	mostrarMenu();
    	
		gotoxy(40, 15); // Ajustar la posición del cursor para la entrada
    	cout<<"Opcion ---> "; cin >> opcion;
    	
    	system("cls");
    	
    	switch(opcion){
    		case '1': GestorDeTareas(); break;
    		case '2': SistemaDeFlashcards(); break;
    		case '3': PonderadoNotas(); break;
    		case '0': cout<< "Saliendo.... \n\nGracias por utilizar ASPE!"<<endl; break;
    		default: cout<<"Opcion invalida o aun no disponible "; getch();
		}
    	
	}while(opcion != '0');
	
    
    
    return 0;
}