#include <iostream>
#include <string>
#include <stdlib.h>
#include "controldeltiempo.h"
//#include "herramientas.h"

using namespace std;

const char *archivoTareas = "infoTareas.dat";
const char *archivoEstadisticasTareas = "estadisticasTareas.dat";

struct Tarea{
	char nombre[31], estado;
	short dias_plazo;
	Fecha fcreacion, fplazo;
};

struct Estadisticas{
	int ntareasCreadas=0, ntareasTerminadas=0, ntareasPorTerminar=0, ntareasVencidas=0;
}eT;

//Contador tareas global
int contTareas;

//Declaracion de las funciones CRUD
void leer();
void crear();
void actualizar();
void eliminar();
void metodos_ordenamiento();
void estadisticasTareas();

//Declaracion de las funciones complementarias
void renovar_tiempos();
string formato_estado(Tarea t);
int calcular_prioridad_estado(char estado);
void verificar_estadisticas();
void actualizar_estadisticas(int valor, int campo);

/*---------------------------------------------------- MAIN ----------------------------------------------------*/
void GestorDeTareas(){
	//SetConsoleOutputCP(CP_UTF8);
	
	int opc;
	string menuTareas[8]{
		"1. Leer Tareas",
		"2. Crear Tarea",
		"3. Actualizar Tarea",
		"4. Eliminar Tarea",
		"5. Metodos de ordenamiento",
		"6. Eliminar todas las tareas guardadas",
		"7. Mostrar resultados estadísticos",
		"\n\tESC. Salir "
	};
	
	do{
		system("CLS");
		
		opc = opcionSeleccionada(menuTareas, "GESTOR DE TAREAS", 8);
		
		verificar_estadisticas(); renovar_tiempos();
		
		switch(opc){
			case 1: leer(); system("pause"); break;
			case 2: crear(); break;
			case 3: actualizar(); break;
			case 4: eliminar(); break;
			case 5: metodos_ordenamiento(); break;
			case 6:{
				//Mensaje de confirmacion a la eliminacion de tareas
				int confirmar;
				leer();
				do{
					cout<<"Esta seguro de eliminar todas las tareas guardadas? ( 1: Si | 0: No ): "; cin>>confirmar;
					if(cin.fail() || (confirmar != 1  && confirmar != 0)) {
						cout<<"\n\n"; colorTextoFondo("Opcion inválida", blancoBrillante, rojo); cout<<"\n\n";
					}
				}while(cin.fail() || (confirmar != 1  && confirmar != 0));
				
				if( confirmar==1 ) { remove(archivoTareas); }
				break;
			}
			case 7: estadisticasTareas(); system("pause"); break;
			case 0: cout << "\n\tVolviendo al menú principal ASPE...\n\n"; system("pause"); break;
		}
	}while(opc != 0);
}

/*------------------------------------------------- FUNCIONES CRUD -------------------------------------------------*/
void crear(){
	//Apertura del archivo y definicion de variables
	int i=1, continuar;
	FILE *archivo = fopen(archivoTareas, "a+b");
	Tarea t;
	
	do{
		//Evita la saturacion de pantalla
		system("CLS");
		cout<<"\n> Crear Tareas";
		cout<<"\n\n Tarea "<<i<<endl<<endl;
		
		fflush(stdin);
		cout<<"\tDigite el nombre de la tarea: "; cin.getline(t.nombre,31,'\n'); cin.clear();
		//Verificar que los dias de plazo sean validos
		do{
			cin.clear();
			fflush(stdin);
			cout<<"\n\tDigite los dias de plazo: "; cin>>t.dias_plazo;
			
			if(cin.fail() || t.dias_plazo < 0) {	
				cout<<"\n\t"; colorTextoFondo("Opcion inválida", blancoBrillante, rojo); cout<<"\n";
			}
		}while( cin.fail() || t.dias_plazo < 0);
		
		t.fcreacion = definir_fecha(0,0,0,0);
        t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
        
		fflush(stdin);
		cout<<"\n\tSeleccione un estado ( T: Terminada | P: Por terminar ): "; cin>>t.estado;
		t.estado = tolower(t.estado);
		
		//Incrementa los contadores del registro historico y los guarda
		switch( t.estado ){
			case 't': actualizar_estadisticas(1,2); break;
			case 'p': actualizar_estadisticas(1,3); break;
			case 'v': actualizar_estadisticas(1,4); break;
		}
		
		fwrite(&t,sizeof(Tarea),1,archivo);
		i++; actualizar_estadisticas(1,1);
		cout<<"\n\t"; colorTextoFondo("Tarea creada con éxito", blancoBrillante, verde);
		
		//Verificar valor de confirmacion
		do{
			cin.clear();
			fflush(stdin);
			cout<<"\n\n\tContinuar creando tareas? ( 1: Si | 0: No ): "; cin>>continuar;
			
			if( (continuar != 1 && continuar !=0) || cin.fail() ) {		
				cout<<"\n\t";colorTextoFondo("Opcion inválida", blancoBrillante, rojo); cout<<"\n\t";
			}
		}while( (continuar != 1 && continuar !=0) || cin.fail() ) ;
		
	}while( continuar == 1 );
	
	fclose(archivo);
}

void leer(){
	//Renovar tiempos antes de visualizar la tabla de tareas
	FILE *archivo = fopen(archivoTareas, "r+b");
	Tarea t;
	
	//INDICAR FECHA ACTUAL
	Fecha ahora = definir_fecha(0,0,0,0);
	gotoxy(0,1); cout<<"> FECHA ACTUAL: "<<formato_fecha(ahora)<<" - "<<formato_hora(ahora);
	
	//TITULOS DE LAS COLUMNAS ACTIVAS
	int id=0, fila=4;
	
	gotoxy(6, fila); cout<<"ID";
	gotoxy(10, fila); cout<<"Nombre";
	gotoxy(45, fila); cout<<"D.Plazo";
	gotoxy(56, fila); cout<<"F.Creacion";
	gotoxy(77, fila); cout<<"F.Plazo";
	gotoxy(98, fila); cout<<"Estado";
	fila++; 
	gotoxy(4, fila); cout<<"-------------------------------------------------------------------------------------------------------------"; fila++;
	
	//IMPRESION DE LOS DATOS DE CADA TAREA ACTIVA
	while( fread(&t, sizeof(Tarea), 1, archivo) ){
		gotoxy(6, fila); cout<<id;
		gotoxy(10, fila); cout<<t.nombre;
		gotoxy(45, fila); cout<<t.dias_plazo;
		gotoxy(56, fila); cout<<formato_fecha(t.fcreacion)<<" - "<<formato_hora(t.fcreacion);
		gotoxy(77, fila); cout<<formato_fecha(t.fplazo)<<" - "<<formato_hora(t.fplazo);
		gotoxy(98, fila); cout<<formato_estado(t);
		fila++; id++;
	}	
	
	fclose(archivo);
	cout<<"\n\n\n";
}

void actualizar(){
	//Visualizacion de las tareas activas
	leer();
	cout<<"> ACTUALIZAR TAREA"<<endl<<endl;
	
	//Apertura de archivos y definicion de variables	
	int id = 0;
	
	//Solicitud del id
	char opcion;
	do{
		cin.clear();
		fflush(stdin);
		
		cout<<"\tId de la Tarea que va actualizar: ";cin>>id;
		if(id<0 || id>(contTareas-1) || cin.fail() ){
			cout<<"\n\t";
			colorTextoFondo("Id no existente", blancoBrillante, rojo);
			cout<<"\n\n";
		}
	}while(id<0 || id > (contTareas-1) || cin.fail() );
    
	do{
		FILE *archivo = fopen(archivoTareas, "r+b");
		Tarea t;
		
		system("cls"); leer();
		
		cout<<"\n\tQue desea actualizar? "<<endl;
		cout<<"\t1.Nombre"<<endl;
		cout<<"\t2.Dias de plazo"<<endl;
		cout<<"\t3.Estado"<<endl;
		cout<<"\t4.Todos los campos"<<endl;
		cout<<"\t0.Salir"<<endl;
		cout<<"\n\tIngrese la opcion:  ";cin>>opcion;
		
		if(opcion != '0'){
			fseek(archivo, id * sizeof(Tarea), SEEK_SET);
			fread(&t, sizeof(Tarea), 1, archivo);
			
			char estadoAntiguo = t.estado;
			
			switch(opcion){
				case '1':{
					fflush(stdin);
					cout<<"\tDigite el nombre de la tarea: "; cin.getline(t.nombre,31,'\n'); cin.clear();
					
					break;
				}
				case '2':{
					fflush(stdin);
					//Verificar que los dias de plazo sean validos
					do{
						cin.clear();
						fflush(stdin);
						cout<<"\n\tDigite los dias de plazo: "; cin>>t.dias_plazo;
						
						if(cin.fail() || t.dias_plazo < 0) {		
							cout<<"\n\t"; colorTextoFondo("Opcion inválida", blancoBrillante, rojo); cout<<endl;
						}
					}while( cin.fail() || t.dias_plazo < 0) ;
					
					t.fcreacion = definir_fecha(0,0,0,0);
					t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
					break;
				}
				case '3':{
					fflush(stdin);
					cout<<"\n\tSeleccione un estado (T: Terminada / P: Por terminar): "; cin>>t.estado;
					
					//Reestablecer el conteo
					switch( estadoAntiguo ){
						case 't': actualizar_estadisticas(-1,2); break;
						case 'p': actualizar_estadisticas(-1,3); break;
						case 'v': actualizar_estadisticas(-1,4); break;
					}
					
					switch( t.estado ){
						case 't': actualizar_estadisticas(1,2); break;
						case 'p': actualizar_estadisticas(1,3); break;
						case 'v': actualizar_estadisticas(1,4); break;;
					}
					
					break;
				}	
				case'4':{
					//Recepcion de datos a cambiar de la tarea elegida
					fflush(stdin);
					cout<<"\tDigite el nombre de la tarea: "; cin.getline(t.nombre,31,'\n'); cin.clear();
					
					//Verificar que los dias de plazo sean validos
					do{
						cin.clear();
						fflush(stdin);
						cout<<"\n\tDigite los dias de plazo: "; cin>>t.dias_plazo;
						
						if(cin.fail() || t.dias_plazo < 0) {
							cout<<"\n\t"; colorTextoFondo("Opcion inválida", blancoBrillante, rojo); cout<<endl;
						}
					}while( cin.fail() || t.dias_plazo < 0) ;
					
					t.fcreacion = definir_fecha(0,0,0,0);
					t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
					
					cout<<"\n\tSeleccione un estado (T: Terminada / P: Por terminar): "; cin>>t.estado;
					
					//Reestablecer el conteo
					switch( estadoAntiguo ){
						case 't': actualizar_estadisticas(-1,2); break;
						case 'p': actualizar_estadisticas(-1,3); break;
						case 'v': actualizar_estadisticas(-1,4); break;
					}
					switch( t.estado ){
						case 't': actualizar_estadisticas(1,2); break;
						case 'p': actualizar_estadisticas(1,3); break;
						case 'v': actualizar_estadisticas(1,4); break;;
					}
					break;
				}
				default: {
					cout<<"\n\t"; colorTextoFondo("Opción inválida", blancoBrillante, rojo);
	            }
	        }
	        
			fseek(archivo, id * sizeof(Tarea), SEEK_SET);  
        	fwrite(&t, sizeof(Tarea), 1, archivo);
        	
			cout<<"\n\t"; colorTextoFondo("Tarea actualizada con éxito", blancoBrillante, verde); cout<<endl;
        }    
		fclose(archivo);
		renovar_tiempos();
		
		cout<<"\n\t"; system("pause");
	}while(opcion != '0');
}

void eliminar(){
	//Visualizacion de las tareas activas
	leer();
	cout<<"> ELIMINAR TAREA"<<endl<<endl;
	
	//Apertura de archivos y definicion de variables
	FILE *archivo = fopen(archivoTareas, "r+b");
	FILE *temp = fopen("temp.dat", "w+b");
	int id=0, id_borrar;
	Tarea t;
	
	//Solicitud del id
	do{
		cin.clear();
		fflush(stdin);
		cout<<"Id de la Tarea que va a eliminar: ";cin>>id_borrar;
		  
		if(id_borrar<0 || id_borrar>(contTareas-1) || cin.fail() ){
			cout<<"\n\n"; colorTextoFondo("Id no existente", blancoBrillante, rojo); cout<<"\n\n";
		}  
		                            
	}while(id_borrar<0 || id_borrar>(contTareas-1) || cin.fail() );
	
	//Duplicado de las tareas del archivo original al temp a excepcion del id		
	for(id=0; id < contTareas ; id++){
		fread(&t, sizeof(Tarea), 1, archivo);
		
		if (id_borrar != id){
			fwrite(&t, sizeof(Tarea), 1, temp);
		}
	}
	fclose(archivo); fclose(temp);
	
	//Pase de las tareas guardadas en temp al archivo original
	archivo = fopen(archivoTareas, "w+b");
	temp = fopen("temp.dat", "r+b");
	
	for(id=0; id < contTareas - 1 ; id++){
		fread(&t, sizeof(Tarea), 1, temp);
		fwrite(&t, sizeof(Tarea), 1, archivo);
	}
	fclose(archivo);
	fclose(temp); remove("temp.dat");
	
	//Visualizacion de los cambios
	system("CLS");
	leer();
	system("pause");
}

void metodos_ordenamiento(){
	Tarea t, aux;
	bool ordenado, condicion, opc_invalida;
	char opc;
	FILE *archivo = fopen(archivoTareas, "r+b");
	
	do{
		//MENU DE OPCIONES PARA LOS METODOS DE ORDENAMIENTO
		system("CLS");
		
		leer();
 		cout<<"> MÉTODOS DE ORDENAMIENTO"<<endl<<endl;
		cout<<"1. Ordenamiento por fecha de creacion"<<endl;
		cout<<"2. Ordenamiento alfabetico (A - Z)"<<endl;
		cout<<"3. Ordenamiento por prioridad (Menores dias de plazo)"<<endl;
		cout<<"4. Ordenamiento por estado (Terminada > Por terminar > Vencida)"<<endl;
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		
		if( opc != '0'){
			do{
				opc_invalida = false;
				ordenado = true;
				
				for(int j=0; j < contTareas - 1; j++){
					fseek(archivo, j * sizeof(Tarea), SEEK_SET);
					fread(&t, sizeof(Tarea), 1, archivo);
					fread(&aux, sizeof(Tarea), 1, archivo);
					
					switch(opc){
						//ORDENAMIENTO POR FECHA DE CREACION
						case '1': condicion = ( t.fcreacion.segreales > aux.fcreacion.segreales ); break;
						
						//ORDENAMIENTO ALFABETICO
						case '2': condicion = ( tolower(t.nombre[0]) > tolower(aux.nombre[0]) ); break;
						
						//ORDENAMIENTO POR PRIORIDAD (MENORES DIAS DE PLAZO)
						case '3': condicion = ( t.dias_plazo > aux.dias_plazo ); break;
						
						//ORDENAMIENTO POR ESTADO (TERMINADO > POR TERMINAR > VENCIDO)
						case '4': condicion = ( calcular_prioridad_estado(t.estado) > calcular_prioridad_estado(aux.estado) ); break;
						
						default: cout<<"\n\n"; colorTextoFondo("Opción Inválida", blancoBrillante, rojo); cout<<"\n\n"; opc_invalida = true; system("pause");
					}
					
					//Control de entrada no deseada
					if(	opc_invalida ){
						break;
					}
					
					if( condicion ){
						ordenado = false;
							
						fseek(archivo, j * sizeof(Tarea), SEEK_SET);
						fwrite(&aux, sizeof(Tarea), 1, archivo);
						fwrite(&t, sizeof(Tarea), 1, archivo);
					}
				}
				
			}while(ordenado == false && opc_invalida == false);
		}
		
	}while( opc != '0');
	
	fclose(archivo);
}

void verificar_estadisticas(){
	FILE *estadisTareas = fopen(archivoEstadisticasTareas, "r+b");
	
	if( !estadisTareas ){
		estadisTareas = fopen(archivoEstadisticasTareas, "w+b");
		
		//Inicialización
		eT = {0,0,0,0};
		fwrite(&eT, sizeof(Estadisticas), 1, estadisTareas);
		fclose(estadisTareas);
	}else{
		fread(&eT, sizeof(Estadisticas), 1, estadisTareas);
		fclose(estadisTareas);
	}
}

void actualizar_estadisticas(int valor, int campo){
	verificar_estadisticas();

	switch (campo) {
		case 1: eT.ntareasCreadas += valor; break;
		case 2: eT.ntareasTerminadas += valor; break;
		case 3: eT.ntareasPorTerminar += valor; break;
		case 4: eT.ntareasVencidas += valor; break;
    }
    
	// Guardar los cambios en el archivo
	FILE *estadisTareas = fopen(archivoEstadisticasTareas, "w+b");
	if( !estadisTareas ){
		cout << "\n\t"; colorTextoFondo("No se pudo abrir el archivo de estadísticas", blancoBrillante, rojo); cout << "\n\n";
		return;
	}
	
	fwrite(&eT, sizeof(Estadisticas), 1, estadisTareas);
	fclose(estadisTareas);
}

void estadisticasTareas(){
	verificar_estadisticas();
	
	cout << "\n\t"; colorTexto("ESTADÍSTICAS DEL GESTOR DE TAREAS", amarilloClaro);
	
	if( eT.ntareasCreadas > 0){
		float porcentTerminadas=0, porcentPorTerminar=0, porcentVencidas=0;
		
		porcentTerminadas = (eT.ntareasTerminadas * 1.0f/eT.ntareasCreadas)*100;
		porcentPorTerminar = (eT.ntareasPorTerminar * 1.0f/eT.ntareasCreadas)*100;
		porcentVencidas = (eT.ntareasVencidas * 1.0f/eT.ntareasCreadas)*100;
		
		
		cout<<"\n\n\t- Tareas Creadas: "<<eT.ntareasCreadas;
		cout<<"\n\t- Tareas Terminadas: "<<eT.ntareasTerminadas<<" ("<<porcentTerminadas<<"%)";
		cout<<"\n\t- Tareas Por Terminar: "<<eT.ntareasPorTerminar<<" ("<<porcentPorTerminar<<"%)";
		cout<<"\n\t- Tareas Vencidas: "<<eT.ntareasVencidas<<" ("<<porcentVencidas<<"%)";
	}else{
		cout << "\n\n\t"; colorTextoFondo("No se encontraron tareas registradas!", blancoBrillante, rojo);
	}

	cout<<"\n\n";
	c1 = eT.ntareasCreadas > 0;
	c2 = eT.ntareasTerminadas > eT.ntareasVencidas;
}

/*-------------------------------------------- FUNCIONES COMPLEMENTARIAS --------------------------------------------*/
string formato_estado(Tarea t){
	switch( tolower(t.estado) ){
		case 't': return "Terminada"; break;
		case 'p': return "Por terminar"; break;
		case 'v': return "Vencida"; break;
		default: return "Estado invalido";
	}
}

void renovar_tiempos() {
    FILE *archivo = fopen(archivoTareas, "r+b");
	if(!archivo){
		archivo = fopen(archivoTareas, "a+b");
		fclose(archivo);
		
		archivo = fopen(archivoTareas, "r+b");
	}
	
    verificar_estadisticas();
	
    Fecha ahora = definir_fecha(0, 0, 0, 0);
    Tarea t;
    int id = 0;

	contTareas = 0;
    while( fread(&t, sizeof(Tarea), 1, archivo) ){
        // Calcular los segundos transcurridos desde la creación de la tarea
        long segreales_pasados = ahora.segreales - t.fcreacion.segreales;
        int dias_pasados = segreales_pasados / 86400; // Convertir segundos a días

        // Descontar los días pasados del plazo de la tarea
        if (dias_pasados > 0) {
            t.dias_plazo -= dias_pasados;
            if (t.dias_plazo < 0) {
                t.dias_plazo = 0; // Evitar valores negativos
            }
        }

        // Actualizar contadores y estado de la tarea si ha cambiado
        if (t.estado == 'p' && t.dias_plazo == 0) {
            actualizar_estadisticas(-1,3);
            actualizar_estadisticas(1,4);
            t.estado = 'v';
            
            // Reescribir la tarea actualizada en el archivo
            fseek(archivo, id * sizeof(Tarea), SEEK_SET);
        	fwrite(&t, sizeof(Tarea), 1, archivo);
        	fseek(archivo, id * sizeof(Tarea), SEEK_SET);
        	
		} else if (t.estado == 'v' && t.dias_plazo > 0) {
			actualizar_estadisticas(-1,4);
            actualizar_estadisticas(1,3);
            t.estado = 'p';
            
            // Reescribir la tarea actualizada en el archivo
            fseek(archivo, id * sizeof(Tarea), SEEK_SET);
        	fwrite(&t, sizeof(Tarea), 1, archivo);
        	fseek(archivo, id * sizeof(Tarea), SEEK_SET);
        }
        id++; contTareas++;
    }

    // Reescribir los contadores modificados
    fclose(archivo);
}

int calcular_prioridad_estado(char estado){
	switch( estado ){
		case 't': return 1; break;
		case 'p': return 2; break;
		case 'v': return 3; break;
		default: return 0;
	}
}