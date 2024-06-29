#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <string>
#include "herramientas.h"
using namespace std;
const char *nombre_archivo_n="notas.dat";
const char *nombre_archivo2_n="analisis.dat";

void gotoxy(int x, int y);
void leer_n();
void crear_n();
void actualizar_n();
void eliminar_n();
void metodos_ordenamiento();
void renovar_tiempos();
void analisis_estadistico();

struct Estudiante{
	
	char curso[31];
	float pc1,parcial,pc2,final,promedio;
	
}notas;

short i=0, j=0, nnotas;

void gotoxy(int x, int y){
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

int main(){
	
	int opc;


	string tituloPonderado = "PONDERADO DE NOTAS";
	string menuPonderado[8] = {
		"1. Leer Notas",
		"2. Crear Notas",
		"3. Actualizar Notas",
		"4. Eliminar Notas",
		"5. Ordenar datos",
		"6. Analisis estadistico",
		"7. Eliminar todas las notas guardadas",		
		"0. Salir"
	};

	do{
        opc = opcionSeleccionada(menuPonderado, tituloPonderado, 8);
		
		system("cls");
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opc) {
			case 1: {
				leer_n();
				break;
			}
			case 2: {
				crear_n();
				break;
			}
			case 3: {
				actualizar_n();
				break;
			}
			case 4: {
				eliminar_n();
				break;
			}
			case 5: {
				metodos_ordenamiento();
				break;
			}
			case 6: {
				analisis_estadistico();
				break;
			}
			case 7: {
								//Mensaje de confirmacion a la eliminacion de tareas
				bool confirmar;
				leer_n();
				cout<<"Esta seguro de eliminar todas las notas guardadas? ( 1: Si | 0: No ): "; cin>>confirmar;
				if( confirmar ){
					remove(nombre_archivo_n);
				}
				break;
			}			
			case 0: {
				system("CLS"); cout<<"Hasta pronto..."<<endl;
				break;
			}
			default: {
				system("CLS"); colorTextoFondo("\n\tOpción no válida. Por favor, seleccione una opción válida.\n\n", blancoBrillante, rojo);
				break;
			}
		}
		system("pause");
		system("cls");
	} while (opc != 0);
	return 0;

}





void leer_n(){
	//Renovar tiempos antes de visualizar la tabla de tareas
	renovar_tiempos();
	system("cls");
	FILE* archivo=fopen(nombre_archivo_n,"rb");
	if(!archivo){
		archivo=fopen(nombre_archivo_n,"w+b");
	}
	Estudiante notas;
	
	//CREACION DE LA TABLA DE TAREAS ACTIVAS
	short id=0, idCol=6, cursoCol=10, pc1Col=45, parcialCol=56, pc2Col=67, finalCol=78, promCol=98, fila=3;
	
	//TITULOS
	gotoxy(idCol, fila); cout<<"ID";
	gotoxy(cursoCol, fila); cout<<"Curso";
	gotoxy(pc1Col, fila); cout<<"PC1";
	gotoxy(parcialCol, fila); cout<<"Parcial";
	gotoxy(pc2Col, fila); cout<<"PC2";
	gotoxy(finalCol, fila); cout<<"Final";
	gotoxy(promCol, fila); cout<<"promedio";
	fila++; 
	gotoxy(4, fila); cout<<"-------------------------------------------------------------------------------------------------------------"; fila++;
	
	//IMPRESION DE LOS DATOS DE CADA TAREA ACTIVA
	while( fread(&notas,sizeof(Estudiante),1,archivo)){
		gotoxy(idCol, fila); cout<<id;
		gotoxy(cursoCol, fila); cout<<notas.curso;
		
		gotoxy(pc1Col, fila); cout<<notas.pc1;
		gotoxy(parcialCol, fila); cout<<notas.parcial;
		gotoxy(pc2Col, fila); cout<<notas.pc2;
		gotoxy(finalCol, fila); cout<<notas.final;
		gotoxy(promCol, fila); cout<<notas.promedio;
		fila++; id++;
	}	
	
	fclose(archivo);
	cout<<endl<<endl<<endl;
}

void crear_n() {
    FILE* archivo = fopen(nombre_archivo_n, "a+b");

    char res;
    cout<<"- [ Creacion de ponderado ] - "<<endl;
    do {
        fflush(stdin);
        cout<< "\n\tIngrese nombre del curso: ";
        cin.getline(notas.curso, 31);

        do {
            cout<<"\n\tIngrese la nota de la PC1:   ---> ";
            cin>>notas.pc1;
            if(notas.pc1 < 0 || notas.pc1 > 20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas.pc1<0 || notas.pc1>20);

        do {
            cout<<"\tIngrese la nota del parcial: ---> ";
            cin>>notas.parcial;
            if(notas.parcial<0 || notas.parcial>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas.parcial<0 || notas.parcial>20);

        do {
            cout<<"\tIngrese la nota de la PC2:   ---> ";
            cin>>notas.pc2;
            if (notas.pc2<0 || notas.pc2>20) {
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas.pc2<0 || notas.pc2>20);

        do {
            cout << "\tIngrese la nota del final:   ---> ";
            cin >> notas.final;
            if (notas.final<0 || notas.final>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas.final<0 || notas.final>20);

        notas.promedio=(notas.pc1*0.2)+(notas.parcial*0.3)+(notas.pc2*0.2)+(notas.final*0.3);

        fwrite(&notas, sizeof(Estudiante), 1, archivo);
        cout<<"\nDesea ingresar notas de otro curso? (s/n): ";
        cin>>res;

    } while(res=='s' || res=='S');

	colorTextoFondo("\n\tDatos guardados exitosamente!!!\n\n", blancoBrillante, verde);
	system("pause");
		
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
        do {
            cout<<"\n\tIngrese la nota de la PC1:   ---> ";
            cin>>notas_existente.pc1;;
            if (notas_existente.pc1<0 || notas_existente.pc1>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while (notas_existente.pc1<0 || notas_existente.pc1>20);

        do {
            cout<<"\tIngrese la nota del parcial: ---> ";
            cin>>notas_existente.parcial;
            if (notas_existente.parcial<0 || notas_existente.parcial>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas_existente.parcial<0 || notas_existente.parcial>20);

        do {
            cout<<"\tIngrese la nota de la PC2:   ---> ";
            cin>>notas_existente.pc2;
            if(notas_existente.pc2<0 || notas_existente.pc2>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas_existente.pc2<0 || notas_existente.pc2>20);

        do {
            cout<<"\tIngrese la nota del final:   ---> ";
            cin>>notas_existente.final;
            if (notas_existente.final<0 || notas_existente.final>20){
                colorTextoFondo("\n\tNota fuera de rango. Ingrese un valor entre 0 y 20.\n\n", blancoBrillante, rojo);
            }
        } while(notas_existente.final<0 || notas_existente.final>20);

    notas_existente.promedio=(notas_existente.pc1*0.2)+(notas_existente.parcial*0.3)+(notas_existente.pc2*0.2)+(notas_existente.final*0.3);
     
    // Mueve el puntero del archivo al registro deseado de nuevo antes de escribir
    fseek(archivo, id * sizeof(Estudiante), SEEK_SET);
    // Escribe el registro actualizado
    fwrite(&notas_existente, sizeof(Estudiante), 1, archivo);

    fclose(archivo);
    leer_n();
}

void eliminar_n(){
	//Visualizacion de las tareas activas
	leer_n();
	cout<<"- [ Eliminar ] - "<<endl<<endl;
	
	//Apertura de archivos y definicion de variables
	short id=0, id_borrar;
	FILE *archivo = fopen(nombre_archivo_n, "r+b");
	FILE *temp = fopen("temp.dat", "w+b");
	
	//Solicitud del id
	fflush(stdin);
	cout<<"Id de la Tarea que va a eliminar: ";cin>>id_borrar;                                
	
	//Duplicado de las tareas del archivo original al temp a excepcion del id
	for(id=0; id < nnotas ; id++){
		fread(&notas, sizeof(Estudiante), 1, archivo);
		
		if (id_borrar != id){
			fwrite(&notas, sizeof(Estudiante), 1, temp);
		}
	}

	fclose(archivo); fclose(temp);
	
	//Pase de las tareas guardadas en temp al archivo original
	archivo = fopen(nombre_archivo_n, "w+b");
	temp = fopen("temp.dat", "r+b");
	
	for(id=0; id < nnotas - 1; id++){
		fread(&notas, sizeof(Estudiante), 1, temp);
		fwrite(&notas, sizeof(Estudiante), 1, archivo);
	}
	
	fclose(archivo); 
	fclose(temp); remove("temp.dat");
	
	//Visualizacion de los cambios
	system("CLS");
	leer_n();
}



void metodos_ordenamiento(){
	Estudiante aux;
	bool ordenado, condicion, opc_invalida;
	char opc;
	FILE *archivo = fopen(nombre_archivo_n, "r+b");
	
	do{
		//MENU DE OPCIONES PARA LOS METODOS DE ORDENAMIENTO
		system("CLS");
		
		leer_n();
		cout<<"- [ Metodos de ordenamiento ] - "<<endl<<endl;
		
		
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
				
				for(j=0; j < nnotas - 1; j++){
					fseek(archivo, j * sizeof(Estudiante), SEEK_SET);
					fread(&notas, sizeof(Estudiante), 1, archivo);
					fread(&aux, sizeof(Estudiante), 1, archivo);
					
					switch(opc){
						//ORDENAMIENTO POR FECHA DE CREACION
						case '1': condicion = ( tolower(notas.curso[0]) > tolower(aux.curso[0]) ); break;
						
						//ORDENAMIENTO DE NOTAS
						case '2': condicion = ( notas.pc1 > aux.pc1 ); break;
						
						case '3': condicion = ( notas.parcial > aux.parcial ); break;
												
						case '4': condicion = ( notas.pc2 > aux.pc2 ); break;
						
						case '5': condicion = ( notas.final > aux.final ); break;
						
						case '6': condicion = ( notas.promedio > aux.promedio ); break;
						
						default: opc_invalida = true; 
						colorTextoFondo("\n\tOpcion invalida\n\n", blancoBrillante, rojo); system("pause");
					}
					
					//Control de entrada no deseada
					if(	opc_invalida ){
						break;
					}
					
					if( condicion ){
						ordenado = false;
							
						fseek(archivo, j * sizeof(Estudiante), SEEK_SET);
						fwrite(&aux, sizeof(Estudiante), 1, archivo);
						fwrite(&notas, sizeof(Estudiante), 1, archivo);
					}
				}
				
			}while(ordenado == false && opc_invalida == false);
		}
		
	}while( opc != '0');
	
	fclose(archivo);
}






void renovar_tiempos(){
	FILE *archivo = fopen(nombre_archivo_n, "r+b");
	
	//Mensaje de comprobacion
	if(archivo){
		cout<<"> Archivo abierto correctamente ";
	}else{
		cout<<"> Problema al abrir el archivo ";
	}
	
	nnotas = 0;
	
	//Renovar dias de plazo (dias que han pasado)
	while( fread(&notas, sizeof(Estudiante), 1, archivo) ){
			nnotas++;
		}

	fclose(archivo);
}


void analisis_estadistico() {
	
	leer_n();
	cout<<"- [ Analisis estadistico ] - "<<endl<<endl;
	
    FILE *archivo = fopen(nombre_archivo_n, "rb");
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int total_cursos = 0;
    float suma_promedios = 0, promedio_ponderado = 0;

    while (fread(&notas, sizeof(Estudiante), 1, archivo)) {
        if (notas.promedio != -1) {
            suma_promedios += notas.promedio;
            total_cursos++;
        }
    }

    if (total_cursos > 0) {
        promedio_ponderado = suma_promedios / total_cursos;
    }

    fclose(archivo);
    
	cout<<"/////////////////////////////////"<<endl<<endl;
    cout<<"\nPromedio ponderado: "<<promedio_ponderado<<endl<<endl;

    string evaluacion;
    if (promedio_ponderado >= 18) {
        evaluacion = "Excelente";
    } else if (promedio_ponderado >= 15) {
        evaluacion = "Bueno";
    } else if (promedio_ponderado >= 12) {
        evaluacion = "Regular";
    } else if (promedio_ponderado >= 10.5) {
        evaluacion = "Falta repasar";
    } else if (promedio_ponderado >= 8) {
        evaluacion = "Necesita aprender mas";
    } else {
        evaluacion = "Tiene que repasar todo";
    }

    cout << "Evaluacion: "<<evaluacion<<endl<<endl;

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
    cout<<"/////////////////////////////////"<<endl<<endl;
    cout<<endl<<endl;
    
    system("pause");
    
    // Preguntar si desea guardar el análisis en un archivo .txt
    char respuesta;
    cout << "\nDesea descargar los datos en un archivo? (s/n): ";
    cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
      
		FILE* archivo2=fopen(nombre_archivo2_n,"a+b");        

	    promedio_ponderado;
	    evaluacion;
		colorTextoFondo("\n\tDatos guardados en analisis.dat", blancoBrillante, verde);
		cout<<endl<<endl;
		fclose(archivo2);
	}
	
    else{
            colorTextoFondo("\n\tNo se pudo crear el archivo...", blancoBrillante, rojo);
            cout<<endl<<endl;
    	}
       
    
}
