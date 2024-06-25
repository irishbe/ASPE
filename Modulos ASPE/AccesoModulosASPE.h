#include <cstdlib>
#include <conio.h>

using namespace std;

short i, j, n, id;
extern short i, j, n, id;

// Declaración de la función
#include "GestorDeTareas.h"
#include "SistemaDeFlashcards.h"
#include "PonderadoNotas.h"
#include "herramientas.h"

//void CerrarPeriodoAcademico();

void AccesoModulosASPE(string perfil){
    int opcModulos;
    string opcionesModulos[4] = {
		"1. Gestor de tareas",
		"2. Sistema de flashcards",
		"3. Ponderado Notas",
		"0. Volver"
	};
    
    do{
    	opcModulos = opcionSeleccionada(opcionesModulos, "Perfil: " + perfil + "\n\n\tModulos ASPE", 4);
		system("cls");
		
    	switch(opcModulos){
    		case 1: GestorDeTareas(); break;
    		case 2: SistemaDeFlashcards(); break;
    		case 3: PonderadoNotas(); break;
    		//case 4: CerrarPeriodoAcademico(); break;
    		case 0: cout<< "\n\tVolviendo\n"; break;
		}
    	cout<<"\n\t"; system("cls");
    	
	}while(opcModulos != 0);
}

//void CerrarPeriodoAcademico();