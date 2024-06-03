#include <iostream>
#include <windows.h>
#include <string>
#include "controldeltiempo.h"

using namespace std;
const char *nombre_archivo = "fichero.dat";

struct Tarea{
	char nombre[31], estado;
	short dias_plazo;
	Fecha fcreacion, fplazo;
};

//Variables globales
short i=0, j=0, ntareas;
Tarea t;
Fecha ahora = definir_fecha(0,0,0,0);

//Declaracion de las funciones CRUD
void leer();
void crear();
void actualizar();
void eliminar();
void metodos_ordenamiento();

//Declaracion de las funciones complementarias
void gotoxy(int x, int y);
string formato_estado(Tarea x);
void renovar_tiempos();
short prioridad_estado(char estado);



/*---------------------------------------------------- MAIN ----------------------------------------------------*/
int main(){
	char opc;
	
	do{
		system("CLS");
		cout<<"\n--------------------------------------------   GESTOR DE TAREAS   --------------------------------------------"<<endl<<endl;
		cout<<"1. Leer Tareas"<<endl;
		cout<<"2. Crear Tarea"<<endl;
		cout<<"3. Actualizar Tarea"<<endl;
		cout<<"4. Eliminar Tarea"<<endl;
		cout<<"5. Realizar un metodo de ordenamiento"<<endl;
		cout<<"6. Eliminar todas las tareas guardadas"<<endl;
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		system("CLS");
		
		ahora = definir_fecha(0,0,0,0);
		
		switch(opc){
			case '1': leer(); system("pause"); break;
			case '2': crear(); break;
			case '3': actualizar(); break;
			case '4': eliminar(); break;
			case '5': metodos_ordenamiento(); break;
			case '6':{
				//Mensaje de confirmacion a la eliminacion de tareas
				bool confirmar;
				leer();
				cout<<"Esta seguro de eliminar todas las tareas guardadas? ( 1: Si | 0: No ): "; cin>>confirmar;
				if( confirmar ){
					remove(nombre_archivo);
				}
				break;
			}
			case '0': system("CLS"); cout<<"Hasta pronto..."<<endl; break;
			default: system("CLS"); cout<<"Opcion invalida"<<endl<<endl; system("pause");
		}
	}while(opc != '0');
	
	return 0;
}



/*------------------------------------------------- FUNCIONES CRUD -------------------------------------------------*/
void crear(){
	//Apertura del archivo y definicion de variables
	i=1;
	bool continuar;
	FILE *archivo = fopen(nombre_archivo, "a+b");
	
	//Solicitud de datos de la tarea a agregar
	cout<<"- [ Creacion de tareas ] - "<<endl;
	
	do{
		//Evita la saturacion de la pantalla
		if( i % 3 == 0){
			system("CLS");
			cout<<"> Crear Tareas";
		}
		
		fflush(stdin);
		cout<<"\n\nTarea "<<i<<endl<<endl;
		cout<<"\tDigite el nombre de la tarea: "; cin.getline(t.nombre,30,'\n');
		cout<<"\tDigite los dias de plazo: "; cin>>t.dias_plazo;
		t.fcreacion = definir_fecha(0,0,0,0);
        t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
        cout<<"\tSeleccione un estado ( T: Terminada | P: Por terminar ): "; cin>>t.estado;
		
		fwrite(&t,sizeof(Tarea),1,archivo);
		
		cout<<"\nContinuar creando tareas? ( 1: Si | 0: No ): "; cin>>continuar;
		i++;	
	}while(continuar);
	
	fclose(archivo);
}

void leer(){
	//Renovar tiempos antes de visualizar la tabla de tareas
	ahora = definir_fecha(0,0,0,0);
	renovar_tiempos();
	
	FILE *archivo = fopen(nombre_archivo, "r+b");
	
	//CREACION DE LA TABLA DE TAREAS ACTIVAS
	short id=0, idCol=6, nombreCol=10, dpCol=45, fcCol=56, fpCol=77, estadoCol=98, fila=3;
	
	//TITULOS
	gotoxy(idCol, fila); cout<<"ID";
	gotoxy(nombreCol, fila); cout<<"Nombre";
	gotoxy(dpCol, fila); cout<<"D.Plazo";
	gotoxy(fcCol, fila); cout<<"F.Creacion";
	gotoxy(fpCol, fila); cout<<"F.Plazo";
	gotoxy(estadoCol, fila); cout<<"Estado";
	fila++; 
	gotoxy(4, fila); cout<<"-------------------------------------------------------------------------------------------------------------"; fila++;
	
	//IMPRESION DE LOS DATOS DE CADA TAREA ACTIVA
	while( fread(&t, sizeof(Tarea), 1, archivo) ){
		gotoxy(idCol, fila); cout<<id;
		gotoxy(nombreCol, fila); cout<<t.nombre;
		
		gotoxy(dpCol, fila); cout<<t.dias_plazo;
		gotoxy(fcCol, fila); cout<<formato_fecha(t.fcreacion)<<" - "<<formato_hora(t.fcreacion);
		gotoxy(fpCol, fila); cout<<formato_fecha(t.fplazo)<<" - "<<formato_hora(t.fplazo);
		gotoxy(estadoCol, fila); cout<<formato_estado(t);
		fila++; id++;
	}	
	
	fclose(archivo);
	cout<<endl<<endl<<endl;
}

void actualizar(){
	//Visualizacion de las tareas activas
	leer();
	cout<<"- [ Actualizar ] - "<<endl<<endl;
	
	//Apertura de archivos y definicion de variables
	short id = 0;
	FILE *archivo = fopen(nombre_archivo, "r+b");
	
	//Solicitud del id
	fflush(stdin);
	cout<<"Id de la Tarea que va actualizar: ";cin>>id;
	fseek(archivo, id * sizeof(Tarea), SEEK_SET);
	
	//Recepcion de datos a cambiar de la tarea elegida
	fflush(stdin);
	cout<<"\n\tDigite el nombre del Tarea: "; cin.getline(t.nombre,30,'\n');
	cout<<"\tDigite los dias de plazo: "; cin>>t.dias_plazo;
	t.fcreacion = definir_fecha(0,0,0,0);
	t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
    cout<<"\tSeleccione un estado (T: Terminada / P: Por terminar): "; cin>>t.estado;
	
	//Ejecucion de cambios
	fwrite(&t,sizeof(Tarea),1,archivo);
	fclose(archivo);
}

void eliminar(){
	//Visualizacion de las tareas activas
	leer();
	cout<<"- [ Eliminar ] - "<<endl<<endl;
	
	//Apertura de archivos y definicion de variables
	short id=0, id_borrar;
	FILE *archivo = fopen(nombre_archivo, "r+b");
	FILE *temp = fopen("temp.dat", "w+b");
	
	//Solicitud del id
	fflush(stdin);
	cout<<"Id de la Tarea que va a eliminar: ";cin>>id_borrar;                                
	
	//Duplicado de las tareas del archivo original al temp a excepcion del id
	for(id=0; id < ntareas ; id++){
		fread(&t, sizeof(Tarea), 1, archivo);
		
		if (id_borrar != id){
			fwrite(&t, sizeof(Tarea), 1, temp);
		}
	}

	fclose(archivo); fclose(temp);
	
	//Pase de las tareas guardadas en temp al archivo original
	archivo = fopen(nombre_archivo, "w+b");
	temp = fopen("temp.dat", "r+b");
	
	for(id=0; id < ntareas - 1; id++){
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
	Tarea aux;
	bool ordenado, condicion, opc_invalida;
	char opc;
	FILE *archivo = fopen(nombre_archivo, "r+b");
	
	do{
		//MENU DE OPCIONES PARA LOS METODOS DE ORDENAMIENTO
		system("CLS");
		
		leer();
		cout<<"- [ Metodos de ordenamiento ] - "<<endl<<endl;
		
		
		cout<<"1. Ordenamiento por fecha de creacion"<<endl;
		cout<<"2. Ordenamiento alfabetico (A - Z)"<<endl;
		cout<<"3. Ordenamiento por prioridad (Menores dias de plazo)"<<endl;
		cout<<"4. Ordenamiento por estado (Terminado > Por terminar > Vencido)"<<endl;
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		
		system("CLS");
		
		if( opc != '0'){
			do{
				opc_invalida = false;
				ordenado = true;
				
				for(j=0; j < ntareas - 1; j++){
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
						case '4': condicion = ( prioridad_estado(t.estado) > prioridad_estado(aux.estado) ); break;
						
						default: opc_invalida = true; cout<<"Opcion invalida"<<endl<<endl; system("pause");
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



/*-------------------------------------------- FUNCIONES COMPLEMENTARIAS --------------------------------------------*/
void gotoxy(int x, int y){
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

string formato_estado(Tarea x){
	string y;
	
	if( tolower(x.estado) == 't'){
		y = "Terminada";
	}
	
    if( tolower(x.estado) == 'p' ){
		//Cambiar a vencido
		if( ahora.segreales >= x.fplazo.segreales){
			y = "Vencido";
		}else{
			y = "Por terminar";
		}
	}
	return y;
}

void renovar_tiempos(){
	FILE *archivo = fopen(nombre_archivo, "r+b");
	
	//Mensaje de comprobacion
	if(archivo){
		cout<<"> Archivo abierto correctamente ";
	}else{
		cout<<"> Problema al abrir el archivo ";
	}
	
	ntareas = 0;
	
	//Renovar dias de plazo (dias que han pasado)
	while( fread(&t, sizeof(Tarea), 1, archivo) ){
		long segreales_pasados = (ahora.segreales - t.fcreacion.segreales);
		
		while( segreales_pasados >= 86400 && t.dias_plazo > 0){
			segreales_pasados -= 86400;
			t.dias_plazo --;
		}
		
		if( t.dias_plazo == 0){
			t.estado = 'v';
		}
		
		ntareas++;
	}
	fclose(archivo);
}

short prioridad_estado(char estado){
	short y = 0;
	switch( tolower(estado) ){
			case 't': y = 1; break;
			case 'p': y = 2; break;
			case 'v': y = 3; break;
	}
	return y;
}
