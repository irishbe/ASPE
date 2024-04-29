#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <locate.h>
#include <ctime>
using namespace std;

const char *nombre_archivo = "archivos.txt";

struct tareas{
    char nombre[30];
    char estado;
	char estadoverdadero = 'P';    
};

void actualizar();
void crear();
void mostrar();
void eliminar();
void marcar();
int main(){
	system("cls");
    int opcion;
	
    do {
        // Mostramos el menú
        cout << "\nMenú de opciones:\n";
        cout << "1. Actualizar\n";
        cout << "2. Crear\n";
        cout << "3. Mostrar\n";
        cout << "4. Eliminar\n";
        cout << "5. Marcar tarea como terminada\n";
        cout << "6. Salir\n";

        // Solicitamos la opción al usuario
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Ejecutamos la función correspondiente según la opción seleccionada
        switch (opcion) {
            case 1:
                actualizar();
                break;
            case 2:
                crear();
                break;
            case 3:
                mostrar();
                break;
            case 4:
                eliminar();
                break;
            case 5:
                marcar();
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
        }

    } while (opcion != 6);

    return 0;
}

void crear(){
	system("cls");
    FILE* variable = fopen(nombre_archivo, "a+b");
    char opcion;
    tareas tarea1;
    
    do{
        fflush(stdin);
        cout << "Ingrese el nombre de la tarea: ";
        cin.getline(tarea1.nombre,30,'\n');
        cout << endl;
        cout << "Ingrese el estado de la tarea (T/P): ";
        cin >> tarea1.estado;
        cout << endl;
        
        fwrite(&tarea1,sizeof(tareas),1,variable);
        
        cout << "¿Desea añadir otra tarea? (S/N): ";
        cin >> opcion;
            
    } while(opcion == 's' || opcion == 'S');
    
    fclose(variable);
    system("cls");
}

void mostrar(){
	while(true){
    system("cls");
    FILE* variable = fopen(nombre_archivo, "rb");
    
    if(!variable){
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    int id = 0;
    tareas tarea1;
    fread(&tarea1,sizeof(tareas),1,variable);
    
    cout << "\tID\tNombre\tEstado\testadoverdadero\n\n";
    
    do{
        cout << "\t" << id << "\t" << tarea1.nombre << "\t" << tarea1.estado << "\t" << tarea1.estadoverdadero<<endl;
        fread(&tarea1,sizeof(tareas),1,variable);
        id++;
        
    } while(!feof(variable));
    
    fclose(variable);
    cout<<endl;
    int n;
    cout<<"Para volver al menu presione introduzca el 0 : ";cin>>n;
    if(n==0){
    	break;
    }
    
  }
	system("cls");
}

void actualizar(){
	system("cls");
    FILE* variable = fopen(nombre_archivo, "r+b");
    
    if(!variable){
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    tareas tarea1;
    int id = 0;
    
    cout << "Ingrese el ID de la tarea que va a modificar: ";
    cin >> id;
    fflush(stdin);
    fseek(variable, id * sizeof(tareas), SEEK_SET);
    
    cout << "Ingrese el nombre de la tarea: ";
    cin.getline(tarea1.nombre,30,'\n');
    cout << endl;
    cout << "Ingrese el estado de la tarea (T/P): ";
    cin >> tarea1.estado;
    cout << endl;
        
    fwrite(&tarea1,sizeof(tareas),1,variable);
    
    fclose(variable);
    
}

void eliminar(){
	system("cls");
    const char *archivo_temporal = "archivos_temp.txt";
    FILE* variable = fopen(nombre_archivo, "rb");
    
    if(!variable){
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    FILE* variable_temp = fopen(archivo_temporal, "w+b");
    tareas tarea1;
    int id = 0;
    int id_n = 0;
    
    cout << "Ingrese el ID de la tarea que va a borrar: ";
    cin >> id;

    while(fread(&tarea1,sizeof(tareas),1,variable)){
        if(id_n != id){
            fwrite(&tarea1,sizeof(tareas),1,variable_temp);
        }
        id_n++;
    }
    
    fclose(variable);
    fclose(variable_temp);
    
    variable_temp = fopen(archivo_temporal,"rb");
    variable = fopen(nombre_archivo,"wb");
    
    while(fread(&tarea1,sizeof(tareas),1,variable_temp)){
        fwrite(&tarea1,sizeof(tareas),1,variable);
    }
    
    fclose(variable);
    fclose(variable_temp);
    cout<<endl;
    cout<<"La tarea fue borrada con exito"<<endl;
}
void marcar(){

    system("cls");
    FILE* variable = fopen(nombre_archivo, "rb");
    
    if(!variable){
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    int id = 0;
    tareas tarea1;
    fread(&tarea1,sizeof(tareas),1,variable);
    
    cout << "\tID\tNombre\tEstado\testadoverdadero\n\n";
    
    do{
        cout << "\t" << id << "\t" << tarea1.nombre << "\t" << tarea1.estado << "\t" << tarea1.estadoverdadero<<endl;
        fread(&tarea1,sizeof(tareas),1,variable);
        id++;
        
    } while(!feof(variable));
    
    fclose(variable);
    cout<<endl;
    
    
    variable = fopen(nombre_archivo, "r+b");
    
    int id2=0;
    cout<<"Escriba el id de la tarea que quiere marcar como entregada : ";
    cin >> id2;
    fflush(stdin);
    fseek(variable, id2 * sizeof(tareas), SEEK_SET);
    
    
    cout << "Ingrese el estado verdadero de la tarea (T) = terminado : ";
    cin >> tarea1.estadoverdadero;
    cout << endl;
        
    fwrite(&tarea1,sizeof(tareas),1,variable);
    
    fclose(variable);
    
    
  

	
}

