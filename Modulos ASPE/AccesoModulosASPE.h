#include <cstdlib>
#include <conio.h>

using namespace std;


bool c1=false, c2=false, c3=false, c4=false, c5=false;
extern bool c1, c2, c3, c4, c5;

// Declaración de la función
#include "herramientas.h"
#include "GestorDeTareas.h"
#include "SistemaDeFlashcards.h"
#include "PonderadoNotas.h"

void CerrarPeriodoAcademico(string &perfil);

void VisualizarResultados(){
	
	estadisticasTareas();
	estadisticasFlashcards();
	estadisticasNotas();
	
	int puntaje=0;
	
	/*
		c1 = eT.ntareasCreadas > 0;
		c2 = eT.ntareasTerminadas > eT.ntareasVencidas;
		c3 = eF.mazosCreados > 0;
		c4 = repasosCompletados > eF.repasosCancelados;
		c5 = promedio_ponderado >= 10.5;
	*/
	
	if(c1) puntaje++; if(c2) puntaje++; if(c3) puntaje++; if(c4) puntaje++; if(c5) puntaje++;
	
	colorTexto("\n\n\t> Usted a lo largo del periodo academico ha presentado un: \n\n", blancoBrillante);
	
	switch(puntaje){
		case 0: colorTextoFondo("\t\tRendimiento Nulo!", blancoBrillante, rojo); break;
		case 1: colorTextoFondo("\t\tRendimiento Muy bajo!", blancoBrillante, rojo); break;
		case 2: colorTextoFondo("\t\tRendimiento Bajo!", blancoBrillante, rojo); break;
		case 3: colorTextoFondo("\t\tRendimiento Considerable!", blancoBrillante, verde); break;
		case 4: colorTextoFondo("\t\tRendimiento Bueno!", blancoBrillante, verde); break;
		case 5: colorTextoFondo("\t\tRendimiento Excelente!", blancoBrillante, verde); break;
	}
	
	cout<<"\n\n\t"; _getch();
}

void AccesoModulosASPE(string perfil){
    int opcModulos;
    string opcionesModulos[5] = {
		"1. Gestor de Tareas",
		"2. Sistema de Flashcards",
		"3. Ponderado Notas",
		"4. Cerrar Periodo Academico",
		"\n\tESC. Salir"
	};
	
	string opcionesCerrado[2] = {"1. Volver a visualizar resultados", "ESC. Salir"};
    
	do{
		if( perfil.substr(perfil.length() - 5) != "#Cerr"){
			
			opcModulos = opcionSeleccionada(opcionesModulos, "Perfil: " + perfil + "\n\n\tModulos ASPE", 5);
			
	   		switch(opcModulos){
	   			case 1: GestorDeTareas(perfil); break;
	   			case 2: SistemaDeFlashcards(); break;
	   			case 3: PonderadoNotas(); break;
	   			case 4: CerrarPeriodoAcademico(perfil); break;
	   			case 0: break;
			}
			
		}else{

	    	opcModulos = opcionSeleccionada(opcionesCerrado, "Perfil: " + perfil + "\n\n\tModulos ASPE", 2);
			
	    	switch(opcModulos){
	   			case 1: VisualizarResultados(); break;
	   			case 0: break;
			}
		}
		
		cout<<"\n\t"; system("cls");
		
	}while(opcModulos != 0);
}

void CerrarPeriodoAcademico(string &perfil){
	VisualizarResultados();
	
	SetCurrentDirectory("..");
	
	string perfilAntes = perfil;
	perfil += " #Cerr";
		
	MoveFile( perfilAntes.c_str(), perfil.c_str() );
		
	SetCurrentDirectory(perfil.c_str());
}