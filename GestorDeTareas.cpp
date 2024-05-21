#include <iostream>
#include <windows.h>
#include "controldeltiempo.h"

using namespace std;
const char *nombre_archivo = "fichero.dat";
Fecha ahora;

struct Tarea{
	char nombre[30], estado;
	unsigned short dias_plazo;
	Fecha fcreacion, fplazo;
};

void leer();
void crear();
void actualizar();
void eliminar();
void ordenar_abc();

void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
} 

string formato_estado(Tarea x){
	string est;
	if(x.estado == 'T' or x.estado =='t'){
		est = "Terminada";
	}
	if(x.estado == 'P' or x.estado == 'p'){
		
		if( formato_fecha(ahora) == formato_fecha(x.fplazo) ){
			est = "Vencida";
		}else{
			est = "Por terminar";
		}
		
	}
	return est;
}

main(){
	char opc;
	
	do{
		system("CLS");
		cout<<"---------------------------------- Menu de opciones ----------------------------------"<<endl<<endl;
		cout<<"1. Leer Tareas"<<endl;
		cout<<"2. Crear Tarea"<<endl;
		cout<<"3. Actualizar Tarea"<<endl;
		cout<<"4. Eliminar Tarea"<<endl;
		cout<<"5. Ordenar por nombre (alfabetico)"<<endl;
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		
		system("CLS");
		ahora = definir_fecha(0,0,0,0);
		
		switch(opc){
			case '1': leer(); system("pause"); break;
			case '2': crear(); break;
			case '3': actualizar(); break;
			case '4': eliminar(); break;
			case '5': ordenar_abc(); break;
			case '0': cout<<"Hasta pronto..."<<endl<<endl; system("pause"); break;
			default: cout<<"Opcion invalida"<<endl<<endl; system("pause");
		}
		
	}while(opc != '0');
}

void crear(){
	bool continuar;
	char est;
	Tarea t;
	FILE *archivo = fopen(nombre_archivo, "a+b");
	
	
	if(archivo){
		cout<<"Archivo abierto correctamente"<<endl<<endl;
	}else{
		cout<<"Problema al abrir el archivo :("<<endl<<endl;
	}
	
	
	do{
		fflush(stdin);
		cout<<"\nDigite el nombre del Tarea: "; cin.getline(t.nombre,30,'\n');
		cout<<"Digite los dias plazo: "; cin>>t.dias_plazo;
		t.fcreacion = definir_fecha(0,0,0,0);
        t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
        cout<<"Seleccione un estado ( T: Terminada | P: Por terminar ): "; cin>>t.estado;
        
		fwrite(&t,sizeof(Tarea),1,archivo);
		
		cout<<"\nContinuar creando tareas? ( 1: Si | 0: No ): "; cin>>continuar;
	}while(continuar);
	
	fclose(archivo);
}

void leer(){
	Tarea t;
	FILE *archivo = fopen(nombre_archivo, "r+b");
	
	if(archivo){
		cout<<"Archivo abierto correctamente"<<endl<<endl;
	}else{
		cout<<"Problema al abrir el archivo :("<<endl<<endl;
	}
	
	short id=0, idCol=10, nombreCol=15, dpCol=45, fcCol=55, fpCol=70, estadoCol=85, fila=3;
	
	gotoxy(idCol, fila); cout<<"ID";
	gotoxy(nombreCol, fila); cout<<"Nombre";
	gotoxy(dpCol, fila); cout<<"D.Plazo";
	gotoxy(fcCol, fila); cout<<"F.Creacion";
	gotoxy(fpCol, fila); cout<<"F.Plazo";
	gotoxy(estadoCol, fila); cout<<"Estado";
	fila++; 
	gotoxy(8, fila); cout<<"-------------------------------------------------------------------------------------------"; fila++;
	
	while( fread(&t, sizeof(Tarea), 1, archivo) ){
		gotoxy(idCol, fila); cout<<id;
		gotoxy(nombreCol, fila); cout<<t.nombre;
		gotoxy(dpCol, fila); cout<<t.dias_plazo;
		gotoxy(fcCol, fila); cout<<formato_fecha(t.fcreacion);
		gotoxy(fpCol, fila); cout<<formato_fecha(t.fplazo);
		gotoxy(estadoCol, fila); cout<<formato_estado(t);
		fila++; id++;
	}	
	
	fclose(archivo);
	cout<<endl<<endl<<endl;
}

void actualizar(){
	leer();
	cout<<endl<<endl<<"--------------------------- Actualizar --------------------------- "<<endl<<endl;
	
	short id=0;
	FILE *archivo = fopen(nombre_archivo, "r+b");
	Tarea t;
	
	
	if(archivo){
		cout<<"Archivo abierto correctamente"<<endl<<endl;
	}else{
		cout<<"Problema al abrir el archivo :("<<endl<<endl;
	}
	
	
	fflush(stdin);
	cout<<"\nId del Tarea a actualizar: ";cin>>id;
	
	fseek(archivo, id * sizeof(Tarea), SEEK_SET);
	
	fflush(stdin);
	cout<<"\nDigite el nombre del Tarea: "; cin.getline(t.nombre,30,'\n');
	cout<<"Digite los dias plazo: "; cin>>t.dias_plazo;
	t.fcreacion = definir_fecha(0,0,0,0);
	t.fplazo = definir_fecha(t.dias_plazo,0,0,0);
    cout<<"Seleccione un estado (T: Terminada / P: Por terminar): ";cin>>t.estado;
	
	fwrite(&t,sizeof(Tarea),1,archivo);
	
	fclose(archivo);
}

void eliminar(){
	leer();
	cout<<endl<<endl<<"--------------------------- Eliminar ---------------------------"<<endl<<endl;
	
	FILE *archivo = fopen(nombre_archivo, "r+b");
	short n=0, id=0, j=0;
	bool ordenado;
	
	
	if(archivo){
		cout<<"Archivo abierto correctamente"<<endl<<endl;
	}else{
		cout<<"Problema al abrir el archivo :("<<endl<<endl;
	}
	
	
	//Definiendo n (cantidad de usuarios)
	fseek(archivo, 0, SEEK_END);
	n = ftell(archivo)/sizeof(Tarea);
	fseek(archivo, 0, SEEK_SET);
	
	Tarea t, temp[n];
	fread(temp, sizeof(Tarea), n, archivo);
	fclose(archivo);
	
	archivo = fopen(nombre_archivo, "w+b");
	fflush(stdin);
	cout<<"\nId de la Tarea a eliminar: ";cin>>id;
	
	
	for(int i=0; i<n; i++){
		if( i != id){
			fwrite(&temp[i], sizeof(Tarea), 1, archivo);
		}
	}
	
	fclose(archivo); system("CLS");
	leer();
	system("pause");
}

void ordenar_abc(){
	//Apertura de archivo y definición de variables
	FILE *archivo = fopen(nombre_archivo, "r+b");	//Modo de lectura en binario (r+b)
	short n=0, id=0, j=0;
	bool ordenado;
	
	//Definiendo n (cantidad de tareas)
	fseek(archivo, 0, SEEK_END);
	
	n = ftell(archivo)/sizeof(Tarea);
	
	fseek(archivo, 0, SEEK_SET);
	
	//Creacion del vector de tareas y almacenando los datos del fichero
	Tarea t, temp[n];
	fread(temp, sizeof(Tarea), n, archivo);
	fclose(archivo);
	
	//Algoritmo de ordenamiento alfabetico
	do{
		ordenado = true;
		
		for(int i=0; i<n-1 ; i++){
			if( temp[i].nombre[0] > temp[i+1].nombre[0] ){
				t = temp[i];
				temp[i] = temp[i+1];
				temp[i+1] = t;
				ordenado = false;
			}
		}

	}while( !ordenado );
	
	//Reescritura del fichero con los usuarios ya reordenados
	archivo = fopen(nombre_archivo, "w+b");
	fwrite(temp, sizeof(Tarea), n, archivo);
	
	//Cerrando el fichero y volviendo a mostrar los usuarios
	fclose(archivo);
	leer();
	system("pause");
}