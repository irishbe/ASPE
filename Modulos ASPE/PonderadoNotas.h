#include <iostream>
#include <windows.h>

using namespace std;
const char *nombre_archivo_n="notas.dat";

//CPP COMO MODULO
void PonderadoNotas();
void leer_n();
void crear_n();
void actualizar_n();

struct Estudiante{
	char curso[31];
	float pc1,parcial,pc2,final,promedio;
	
}notas;

void gotoxy2(int x, int y){
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

void PonderadoNotas(){
	char opc;
	
	do{
		system("CLS");
		cout<<"\n--------------------------------------------   CALCULO DE PONDERADO   --------------------------------------------"<<endl<<endl;
		cout<<"1. Leer Notas"<<endl;
		cout<<"2. Crear Notas"<<endl;
		cout<<"3. Actualizar Notas"<<endl;
		cout<<"4. Eliminar Notas"<<endl;
		cout<<"5. Ordenar datos"<<endl;
		cout<<"6. Eliminar todas las tareas guardadas"<<endl;
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		system("CLS");
		
		
		switch(opc){
			case '1': leer_n(); system("pause"); break;
			case '2': crear_n(); break;
			case '3': actualizar_n(); break;
			//case '4': eliminar(); break;
			//case '5': metodos_ordenamiento(); break;
			case '6':{
				//Mensaje de confirmacion a la eliminacion de tareas
				bool confirmar;
				leer_n();
				cout<<"Esta seguro de eliminar todas las tareas guardadas? ( 1: Si | 0: No ): "; cin>>confirmar;
				if( confirmar ){
					remove(nombre_archivo_n);
				}
				break;
			}
			case '0': system("CLS"); cout<<"Hasta pronto..."<<endl; system("pause"); break;
			default: system("CLS"); cout<<"Opcion invalida"<<endl<<endl; system("pause");
		}
	}while(opc != '0');
}





void leer_n(){
	//Renovar tiempos antes de visualizar la tabla de tareas
	system("cls");
	FILE* archivo=fopen(nombre_archivo_n,"rb");
	if(!archivo){
		archivo=fopen(nombre_archivo_n,"w+b");
	}
	Estudiante notas;
	
	//CREACION DE LA TABLA DE TAREAS ACTIVAS
	short id=0, idCol=6, cursoCol=10, pc1Col=45, parcialCol=56, pc2Col=67, finalCol=78, promCol=98, fila=3;
	
	//TITULOS
	gotoxy2(idCol, fila); cout<<"ID";
	gotoxy2(cursoCol, fila); cout<<"Curso";
	gotoxy2(pc1Col, fila); cout<<"PC1";
	gotoxy2(parcialCol, fila); cout<<"Parcial";
	gotoxy2(pc2Col, fila); cout<<"PC2";
	gotoxy2(finalCol, fila); cout<<"Final";
	gotoxy2(promCol, fila); cout<<"promedio";
	fila++; 
	gotoxy2(4, fila); cout<<"-------------------------------------------------------------------------------------------------------------"; fila++;
	
	//IMPRESION DE LOS DATOS DE CADA TAREA ACTIVA
	while( fread(&notas,sizeof(Estudiante),1,archivo)){
		gotoxy2(idCol, fila); cout<<id;
		gotoxy2(cursoCol, fila); cout<<notas.curso;
		
		gotoxy2(pc1Col, fila); cout<<notas.pc1;
		gotoxy2(parcialCol, fila); cout<<notas.parcial;
		gotoxy2(pc2Col, fila); cout<<notas.pc2;
		gotoxy2(finalCol, fila); cout<<notas.final;
		gotoxy2(promCol, fila); cout<<notas.promedio;
		fila++; id++;
	}	
	
	fclose(archivo);
	cout<<endl<<endl<<endl;
}


void crear_n(){
	FILE* archivo=fopen(nombre_archivo_n,"a+b");
	
	char res;
	
	cout<<"- [ Creacion de ponderado ] - "<<endl;
	do{
		fflush(stdin);
		//cin.ignore();
		cout<<"\n\tIngrese nombre del curso: ";
		cin.getline(notas.curso,31);	

		cout<<"\n\tIngrese la nota de la PC1:   ---> ";
		cin>>notas.pc1;
		
		cout<<"\tIngrese la nota del parcial: ---> ";
		cin>>notas.parcial;
		
		cout<<"\tIngrese la nota de la PC2:   ---> ";
		cin>>notas.pc2;
		
		cout<<"\tIngrese la nota del final:   ---> ";
		cin>>notas.final;
		
		notas.promedio=(notas.pc1*0.2)+(notas.parcial*0.3)+(notas.pc2*0.2)+(notas.final*0.3);

		fwrite(&notas,sizeof(Estudiante),1,archivo);
		cout<<"\nDesea ingresar notas de otro curso? (s/n): ";
		cin>>res;
	}while(res=='s'||res=='S');
	
	fclose(archivo);
	leer_n();
}


void actualizar_n(){
    leer_n();
    FILE* archivo = fopen(nombre_archivo_n, "r+b");
    if(!archivo){
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int id = 0;
    cout << "Ingrese ID del curso para modificar: ";
    cin >> id;
    
    // Mueve el puntero del archivo al registro deseado
    fseek(archivo, id * sizeof(Estudiante), SEEK_SET);
    
    Estudiante notas_existente;
    // Lee el registro existente
    fread(&notas_existente, sizeof(Estudiante), 1, archivo);
    
    // Actualiza solo las notas, el nombre del curso se mantiene
    cout << "\n\tIngrese la nota de la PC1:   ---> ";
    cin >> notas_existente.pc1;        
    cout << "\tIngrese la nota del parcial: ---> ";
    cin >> notas_existente.parcial;        
    cout << "\tIngrese la nota de la PC2:   ---> ";
    cin >> notas_existente.pc2;        
    cout << "\tIngrese la nota del final:   ---> ";
    cin >> notas_existente.final;
    
    notas_existente.promedio = (notas_existente.pc1 * 0.2) + (notas_existente.parcial * 0.3) + (notas_existente.pc2 * 0.2) + (notas_existente.final * 0.3);
    
    // Mueve el puntero del archivo al registro deseado de nuevo antes de escribir
    fseek(archivo, id * sizeof(Estudiante), SEEK_SET);
    // Escribe el registro actualizado
    fwrite(&notas_existente, sizeof(Estudiante), 1, archivo);

    fclose(archivo);
    leer_n();
}