#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

using namespace std;

struct flashcard{
	string tema;
	string contenido;
	int id;
	
};
//Nombre del directorio o carpeta
const string directorio = "Sistema de Flashcards";

string ruta(string nombreArchivo){
	return (directorio + "/" + nombreArchivo + ".txt");
}

void escribir();
void lectura();
void aniadir();

void MenuCartas();
void crearMazo();
void mostrarMazos();
void renombrarMazo();
void eliminarMazo();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();


int main() {
	string opcion;
	
	// Crear el directorio  o carpeta
	if (_mkdir(directorio.c_str())) {
		cout << "Ha ocurrido un error en la creación de la carpeta";
	}
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nCONTENEDOR DE FLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Crear mazo\n";
        cout << "2. Mostrar mazos\n";
        cout << "3. Renombrar mazo\n";
        cout << "4. Eliminar mazo\n";
        cout << "0. Salir\n";
        
        // Solicitamos la opción al usuario
		fflush(stdin);
		cout << "Seleccione una opción: ";
		getline(cin, opcion);
		
		// Limpiamos la pantalla
		system("cls");
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opcion[0]) {
			case '1': {
				crearMazo();
				break;
			}
			case '2': {
				mostrarMazos();
				break;
			}
			case '3': {
				renombrarMazo();
				break;
			}
			case '4': {
				eliminarMazo();
				break;
			}
			case '0': {
				cout << "Saliendo del programa..." << endl;
				system("pause");
				break;
			}
			default: {
				cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
				system("pause");
				break;
			}
		}
		system("cls");
	} while (opcion[0] != '0');
}

void menuCartas() {
	int opcion;
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nFLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Añadir flashcards\n";
        cout << "2. Mostrar flashcards\n";
        cout << "3. Editar flashcards\n";
        cout << "4. Eliminar flashcard\n";
        cout << "0. Salir\n";
        
        // Solicitamos la opción al usuario
		cout << "Seleccione una opción: ";
		cin >> opcion;
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opcion) {
			case 1: {
				//-----------------------
				break;
			}
			case 2: {
				//-----------------------
				break;
			}
			case 3: {
				//-----------------------
				break;
			}
			case 4: {
				//-----------------------
				break;
			}
			default: {
				cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
				break;
			}
		}
	} while (opcion != 0);
}

void crearMazo() {
	string nombreMazo;
	
	fflush(stdin);
	cout << "Nombre del mazo: "; getline(cin, nombreMazo);
	
	// Crea un archivo en una carpeta
	ofstream archivo(ruta(nombreMazo));
	
	if(archivo.fail()) {
		cout << "No se pudo crear el mazo" << endl;
	}
	
	archivo.close();
}

void mostrarMazos() {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	if (verificador != -1) {
		do {
			cout << archivo.name << endl;
		} while (_findnext(verificador, &archivo) == 0);
		
		_findclose(verificador);	
	} else {
		cout << "No se encontraron mazos en el directorio" << endl;
	}
}

void renombrarMazo() {
	mostrarMazos();
	string antiguo, nuevo;
	
	fflush(stdin);
	cout << "Nombre del mazo que desea renombrar: "; getline(cin, antiguo);
	cout << "Nuevo nombre del mazo: "; getline(cin, nuevo);
	
	if (rename (ruta(antiguo).c_str(), ruta(nuevo).c_str() ) != 0) {
        cout << "Error al renombrar el mazo." << endl;
    } else {
    	cout << "El nombre del mazo se ha cambiado correctamente" << endl;
	}
    
}

void eliminarMazo() {
	mostrarMazos();
	string nombreMazo;
	
	fflush(stdin);
	cout << "Nombre del mazo que desea eliminar: "; getline(cin, nombreMazo);
	
	if (remove( ruta(nombreMazo).c_str() ) != 0) {
        cout << "Error al eliminar el mazo." << endl;
    } else {
    	cout << "El mazo se ha eliminado correctamente" << endl;
	}
}

//ELIMianRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

void lectura(){
	ifstream archivo; //-----Escribir texto
	string texto;
	
	archivo.open("flashcards.txt",ios::in); //Abrir el archivo en modo lectura
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		return;
	}
	
	while(getline(archivo, texto)){ //Mientras el archivo no esté en el final
		cout<<texto<<endl;
	}
	
	archivo.close();
}

void aniadir(){
	ofstream archivo; //Abrir el archivo para escritura
	string texto;
	
	archivo.open("flashcards.txt",ios::app); //Abrimos el archivo en modo añadir
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		return;
	}
	
	cout<<"Digite el texto que quiere añadir: ";
	getline(cin, texto);
	
	archivo<<texto<<endl;
	
	archivo.close(); //Cerramos el archivo
}