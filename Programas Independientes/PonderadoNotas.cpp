#include <iostream>
#include <sstream>
#include <string>
#include "herramientas.h"

using namespace std;
const char *archivoNotas ="notas.dat";
const char *archivoEstadisticasNotas ="estadisticasNotas.dat";

void leerNotas();
void crearNotas();
void actualizarNotas();
void eliminarNotas();
void ordenarNotas();
void estadisticasNotas();

struct Notas{
  float valor=0;
  bool llenado=false;
};

struct Curso{
	char nombre[31];
	Notas pc1,parcial,pc2,final;
	float promedio;
};

int cantNotas;

int main(){
	SetConsoleOutputCP(CP_UTF8);
	
	int opc;

	string tituloPonderado = "PONDERADO DE NOTAS";
	string menuPonderado[8] = {
		"1. Leer cursos",
		"2. Crear curso",
		"3. Actualizar curso",
		"4. Eliminar curso",
		"5. Ordenar notas de cursos",
		"6. Analisis estadistico Notas / Cursos",
		"7. Eliminar todas los cursos guardados",		
		"\n\tESC. Salir"
	};

	do{
        opc = opcionSeleccionada(menuPonderado, tituloPonderado, 8);
		
		system("cls");
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opc) {
			case 1: {
				leerNotas();
				break;
			}
			case 2: {
				crearNotas();
				break;
			}
			case 3: {
				actualizarNotas();
				break;
			}
			case 4: {
				eliminarNotas();
				break;
			}
			case 5: {
				ordenarNotas();
				break;
			}
			case 6: {
				estadisticasNotas();
				break;
			}
			case 7: {
				//Mensaje de confirmacion a la eliminacion de todos los cursos
				bool confirmar;
				leerNotas();
				cout<<"Esta seguro de eliminar todas las notas guardadas? ( 1: Si | 0: No ): "; cin>>confirmar;
				if( confirmar ){
					remove(archivoNotas);
				}
				break;
			}			
			case 0: {
				break;
			}
		}
		system("pause");
		system("cls");
	} while (opc != 0);
	return 0;
}

void leerNotas(){
	FILE* archivo=fopen(archivoNotas,"rb");
	Curso c;
	
	if(!archivo){
		archivo=fopen(archivoNotas,"w+b");
	}
	
	//CREACION DE LA TABLA DE TAREAS ACTIVAS
	short id=0, idCol=6, cursoCol=10, pc1Col=45, parcialCol=56, pc2Col=67, finalCol=78, promCol=98, fila=3;
	
	//TITULOS
	gotoxy(6, fila); cout<<"ID";
	gotoxy(10, fila); cout<<"Curso";
	gotoxy(45, fila); cout<<"PC1";
	gotoxy(56, fila); cout<<"Parcial";
	gotoxy(67, fila); cout<<"PC2";
	gotoxy(78, fila); cout<<"Final";
	gotoxy(98, fila); cout<<"promedio";
	
	fila++;
	gotoxy(4, fila); cout<<"-------------------------------------------------------------------------------------------------------------"; fila++;
	
	//IMPRESION DE LOS DATOS DE CADA TAREA ACTIVA
	cantNotas=0;
	while( fread(&c,sizeof(Curso),1,archivo) ){
		
		gotoxy(6, fila); cout<<id;
		gotoxy(10, fila); cout<<c.nombre;
		
		gotoxy(45, fila); if(c.pc1.llenado) {cout<<c.pc1.valor;} else{cout<<"---";}
		gotoxy(56, fila); if(c.parcial.llenado) {cout<<c.parcial.valor;} else{cout<<"---";}
		gotoxy(67, fila); if(c.pc2.llenado) {cout<<c.pc2.valor;} else{cout<<"---";}
		gotoxy(78, fila); if(c.final.llenado) {cout<<c.final.valor;} else{cout<<"---";}
		gotoxy(98, fila); cout << c.promedio;
		fila++; id++; cantNotas++;
	}	
	
	fclose(archivo); cout<<"\n\n\n";
}

void crearNotas() {
    FILE* archivo = fopen(archivoNotas, "a+b");
    
    char res, agregar;
    int i=1;
    cout<<"\n\n\t"; colorTexto("CREACIÓN DE CURSOS", blancoBrillante);
    
    do{
    	Curso c;
    	cout<<"\n\n\tCurso "<<i;
    	
    	fflush(stdin);
		cout << "\n\n\tIngrese nombre del curso: "; cin.getline(c.nombre, 31, '\n'); cin.clear();
		
    	fflush(stdin);
    	cout << "\tEmpezar a agregar notas en " << c.nombre << "? (s/n): "; cin >> agregar;
		
		int opc=1;
		while( (agregar == 's' || agregar == 'S') && opc != 0){
			
			system("cls");
			string opcionesNotas [5] = {"1. Nota PC1", "2. Nota Parcial", "3. Nota PC2", "4. Nota Final", "\n\tESC. Salir"};
		
			//Impresion de valores segun si esta llenado o no la nota
			string pc1 = "\n\n\tPC1: " + (c.pc1.llenado ? to_string(c.pc1.valor) : "---");
			string parcial = " | Parcial: " + (c.parcial.llenado ? to_string(c.parcial.valor) : "---");
			string pc2 = " | PC2: " + (c.pc2.llenado ? to_string(c.pc2.valor) : "---");
			string final = " | Final: " + (c.final.llenado ? to_string(c.final.valor) : "---");
		
			//Concatenacion de strings
			string titulo = "> Nombre del curso: " + string(c.nombre) + pc1 + parcial + pc2 + final + "\n\n\tAgregar nota en...";
			
			opc = opcionSeleccionada(opcionesNotas, titulo, 5);
			
			switch(opc){
				case 1:{
					do{
						cin.clear();
			            cout<<"\n\tIngrese la nota de la PC1:   ---> "; cin>>c.pc1.valor;
			            if(c.pc1.valor < 0 || c.pc1.valor > 20 || cin.fail() ){
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        }while( c.pc1.valor<0 || c.pc1.valor>20 || cin.fail() ); c.pc1.llenado = true;
					break;
				}
				case 2:{
					do {
						cin.clear();
			            cout<<"\n\tIngrese la nota del parcial: ---> ";  cin>>c.parcial.valor;
			            if(c.parcial.valor<0 || c.parcial.valor>20 || cin.fail()){
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        } while(c.parcial.valor<0 || c.parcial.valor>20 || cin.fail()); c.parcial.llenado = true;
					break;
				}
				case 3:{
					do {
						cin.clear();
			            cout<<"\n\tIngrese la nota de la PC2:   ---> "; cin>>c.pc2.valor;
			            if (c.pc2.valor<0 || c.pc2.valor>20|| cin.fail()) {
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        } while(c.pc2.valor<0 || c.pc2.valor>20|| cin.fail()); c.pc2.llenado = true;
					break;
				}
				case 4:{
					do {
						cin.clear();
			            cout << "\n\tIngrese la nota del final:   ---> "; cin >> c.final.valor;
			            if (c.final.valor<0 || c.final.valor>20|| cin.fail()){
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        } while(c.final.valor<0 || c.final.valor>20|| cin.fail()); c.final.llenado = true;
					break;
				}
				case 0:{
					break;
				}
			}
		}
	
	    c.promedio=(c.pc1.valor*0.2)+(c.parcial.valor*0.3)+(c.pc2.valor*0.2)+(c.final.valor*0.3);
		fwrite(&c,sizeof(Curso),1,archivo);
		
		fflush(stdin);
	    cout<<"\tIngresar crear otro curso? (s/n): ";
		cin>>res;
		i++;
		
    }while(res=='s' || res=='S');

	cout<<"\n\t"; colorTextoFondo("Datos guardados exitosamente!!!", blancoBrillante, verde); cout<<"\n\n\t";
	
	system("pause"); system("cls");
		
    fclose(archivo);
    leerNotas();
}

void actualizarNotas(){
    leerNotas();
    FILE* archivo = fopen(archivoNotas, "r+b");
    Curso c;
    
    if(!archivo){
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int id = 0;
    do{
		cin.clear();
		fflush(stdin);
		
		cout<<"\tId de la nota que va actualizar: ";cin>>id;
		if(id<0 || id>(cantNotas-1) || cin.fail() ){
			cout<<"\n\t";
			colorTextoFondo("Id no existente", blancoBrillante, rojo);
			cout<<"\n\n";
		}
	}while(id<0 || id > (cantNotas-1) || cin.fail() );
    
    // Mueve el puntero del archivo al registro deseado
    fseek(archivo, id * sizeof(Curso), SEEK_SET);
    
    // Lee el registro existente
    fread(&c, sizeof(Curso), 1, archivo);
    
    // Actualiza solo las notas, el nombre del curso se mantiene
    int opc;
	do{
		system("cls");
		string opcionesNotas [5] = {"1. Nota PC1", "2. Nota Parcial", "3. Nota PC2", "4. Nota Final", "\n\tESC. Salir"};
		
		//Impresion de valores segun si esta llenado o no la nota
		string pc1 = "\n\n\tPC1: " + (c.pc1.llenado ? to_string(c.pc1.valor) : "---");
		string parcial = " | Parcial: " + (c.parcial.llenado ? to_string(c.parcial.valor) : "---");
		string pc2 = " | PC2: " + (c.pc2.llenado ? to_string(c.pc2.valor) : "---");
		string final = " | Final: " + (c.final.llenado ? to_string(c.final.valor) : "---");
		
		//Concatenacion de strings
		string titulo = "> Nombre del curso: " + string(c.nombre) + pc1 + parcial + pc2 + final + "\n\n\tAgregar nota en...";
				
		opc = opcionSeleccionada(opcionesNotas, titulo, 5);
			
		switch(opc){
			case 1:{
					do{
						cin.clear();
			            cout<<"\n\tIngrese la nota de la PC1:   ---> "; cin>>c.pc1.valor;
			            if(c.pc1.valor < 0 || c.pc1.valor > 20 || cin.fail()){
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        }while(c.pc1.valor<0 || c.pc1.valor>20 || cin.fail()); c.pc1.llenado = true;
					break;
				}
			case 2:{
					do {
						cin.clear();
			            cout<<"\n\tIngrese la nota del parcial: ---> "; cin>>c.parcial.valor;
			            if(c.parcial.valor<0 || c.parcial.valor>20 || cin.fail()){
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        } while(c.parcial.valor<0 || c.parcial.valor>20 || cin.fail()); c.parcial.llenado = true;
					break;
				}
			case 3:{
					do {
						cin.clear();
			            cout<<"\n\tIngrese la nota de la PC2:   ---> "; cin>>c.pc2.valor;
			            if (c.pc2.valor<0 || c.pc2.valor>20 || cin.fail()) {
			                cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
			            }
			        } while(c.pc2.valor<0 || c.pc2.valor>20 || cin.fail()); c.pc2.llenado = true;
					break;
				}
			case 4:{
				do {
					cin.clear();
		            cout << "\n\tIngrese la nota del final:   ---> "; cin >> c.final.valor;
		            if (c.final.valor<0 || c.final.valor>20 || cin.fail()){
		               cout<<"\n\t"; colorTextoFondo("Nota fuera de rango. Ingrese un valor entre 0 y 20.", blancoBrillante, rojo); cout<<"\n\n";
		            }
		        } while(c.final.valor<0 || c.final.valor>20 || cin.fail()); c.final.llenado = true;
				break;
			}
			case 0:{
				break;
			}
		}
	}while( opc != 0);
	
	c.promedio=(c.pc1.valor*0.2)+(c.parcial.valor*0.3)+(c.pc2.valor*0.2)+(c.final.valor*0.3);
	 
    // Mueve el puntero del archivo al registro deseado de nuevo antes de escribir
    fseek(archivo, id * sizeof(Curso), SEEK_SET);
    // Escribe el registro actualizado
    fwrite(&c, sizeof(Curso), 1, archivo);

    fclose(archivo);
    leerNotas();
}

void eliminarNotas(){
	//Visualizacion de las tareas activas
	leerNotas();
	
	cout<<"\n\n\t" ; colorTexto("ELIMINAR NOTAS", blancoBrillante); cout<<"\n\n";
	
	//Apertura de archivos y definicion de variables
	short id=0, id_borrar;
	FILE *archivo = fopen(archivoNotas, "r+b");
	FILE *temp = fopen("temp.dat", "w+b");
	Curso c;
	
	//Solicitud del id
	do{
		cin.clear();
		fflush(stdin);
		
		cout<<"\tId de la nota a eliminar: ";cin>>id_borrar;
		if(id_borrar<0 || id_borrar > (cantNotas-1) || cin.fail() ){
			cout<<"\n\t";
			colorTextoFondo("Id no existente", blancoBrillante, rojo);
			cout<<"\n\n";
		}
	}while(id_borrar<0 || id_borrar > (cantNotas-1) || cin.fail() );                           
	
	//Duplicado de las tareas del archivo original al temp a excepcion del id
	for(id=0; id < cantNotas ; id++){
		fread(&c, sizeof(Curso), 1, archivo);
		
		if (id_borrar != id){
			fwrite(&c, sizeof(Curso), 1, temp);
		}
	}

	fclose(archivo); fclose(temp);
	
	//Pase de las tareas guardadas en temp al archivo original
	archivo = fopen(archivoNotas, "w+b");
	temp = fopen("temp.dat", "r+b");
	
	for(id=0; id < cantNotas - 1; id++){
		fread(&c, sizeof(Curso), 1, temp);
		fwrite(&c, sizeof(Curso), 1, archivo);
	}
	
	fclose(archivo); 
	fclose(temp); remove("temp.dat");
	
	//Visualizacion de los cambios
	system("CLS");
	leerNotas();
}

void ordenarNotas(){
	bool ordenado, condicion, opc_invalida;
	char opc;
	FILE *archivo = fopen(archivoNotas, "r+b");
	
	do{
		//MENU DE OPCIONES PARA LOS METODOS DE ORDENAMIENTO
		Curso c, aux;
		
		system("CLS");
		
		leerNotas();
		cout<<"\n\t"; colorTexto("MÉTODOS DE ORDENAMIENTO", blancoBrillante); cout<<"\n\n";
		
		cout<<"1. Ordenamiento por nombre del curso"<<endl;
		cout<<"2. Ordenamiento de notas PC1 (menor a mayor)"<<endl;
		cout<<"3. Ordenamiento de notas Parcial (menor a mayor)"<<endl;
		cout<<"4. Ordenamiento de notas PC2 (menor a mayor)"<<endl;
		cout<<"5. Ordenamiento de notas Final (menor a mayor)"<<endl;
		cout<<"6. Ordenamiento de notas promedio (menor a mayor)"<<endl;		
		cout<<"0. SALIR "<<endl;
		
		cout<<"\nOPCION ---> ";cin>>opc;
		
		system("CLS");
		
		if( opc != '0'){
			do{
				opc_invalida = false;
				ordenado = true;
				
				for(int j=0; j < cantNotas - 1; j++){
					fseek(archivo, j * sizeof(Curso), SEEK_SET);
					fread(&c, sizeof(Curso), 1, archivo);
					fread(&aux, sizeof(Curso), 1, archivo);
					
					switch(opc){
						case '1': condicion = ( tolower(c.nombre[0]) > tolower(aux.nombre[0]) ); break;
						
						//ORDENAMIENTO DE NOTAS
						case '2': condicion = ( c.pc1.valor > aux.pc1.valor ); break;
						
						case '3': condicion = ( c.parcial.valor > aux.parcial.valor ); break;
												
						case '4': condicion = ( c.pc2.valor > aux.pc2.valor ); break;
						
						case '5': condicion = ( c.final.valor > aux.final.valor ); break;
						
						case '6': condicion = ( c.promedio > aux.promedio ); break;
						
						default: opc_invalida = true; 
						cout<<"\n\t"; colorTextoFondo("Opcion invalida", blancoBrillante, rojo); cout<<"\n\n";
						system("pause");
					}
					
					//Control de entrada no deseada
					if(	opc_invalida ){
						break;
					}
					
					if( condicion ){
						ordenado = false;
							
						fseek(archivo, j * sizeof(Curso), SEEK_SET);
						fwrite(&aux, sizeof(Curso), 1, archivo);
						fwrite(&c, sizeof(Curso), 1, archivo);
					}
				}
				
			}while(ordenado == false && opc_invalida == false);
		}
		
	}while( opc != '0');
	
	fclose(archivo);
}

void estadisticasNotas(){
	cout<<"\n\t"; colorTexto("Resultados de las Notas", blancoBrillante); cout<<"\n\n";
		
    FILE *archivo = fopen(archivoNotas, "rb");
    Curso c;
    
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int total_cursos = 0;
    float suma_promedios = 0, promedio_ponderado = 0;

    while (fread(&c, sizeof(Curso), 1, archivo)) {
        if (c.promedio != -1) {
            suma_promedios += c.promedio;
            total_cursos++;
        }
        cout<<"- Promedio de "<<c.nombre<<": "<<c.promedio<<endl;
    }

    if (total_cursos > 0) {
        promedio_ponderado = suma_promedios / total_cursos;
    }

    fclose(archivo);
	cout<<"\nPromedio ponderado: "<<promedio_ponderado<<endl<<endl;

    // Gráfico de barras
    cout << "Grafico de barras: "<<endl<<endl;
    cout << "|";
    for (int i = 0; i <= 20; i++) {
        if (i == static_cast<int>(promedio_ponderado)) {
            cout << "^";
        } else {
            cout << "-";
        }
    }
    cout<<"|"<<endl;
    cout<<"0         10         20" <<endl<<endl;;
    cout<<endl<<endl;
}