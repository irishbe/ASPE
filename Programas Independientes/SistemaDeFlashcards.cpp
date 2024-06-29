#include <iostream>
#include <fstream>
#include <string>
#include "herramientas.h"
#include <windows.h>

using namespace std;

// Nombre del directorio o carpeta para almacenar los mazos
const string directorio = "Mazos ASPE";
const string dirRepaso = "Repaso";
const string dirEstadisticas = "Estadisticas Flashcards";

//Variables globales
int nMazos = 0, idMazo, idFlashcard, idFlashcardUsuario;
string tema, contenido, *nombresMazos = nullptr;

//Estructura de las estadísticas
struct estadisticasFlashcards{
	int mazosCreados = 0,
		mazosEliminados = 0,
		repasosTotales = 0,
		repasosCancelados = 0,
		puntuacion1 = 0,
		puntuacion2 = 0,
		puntuacion3 = 0;
}eF;

//Funciones para generar rutas
string ruta(string nombreArchivo) {
	return (directorio + "\\" + nombreArchivo);
}
string rutaRepaso(string nombreArchivo) {
	return (directorio + "\\" + dirRepaso + "\\" + nombreArchivo);
}
string rutaEstadistica(string nombreArchivo) {
	return directorio + "\\" + dirEstadisticas + "\\" + nombreArchivo;
}

//Funciones de utilidad
void verificarMazos() {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	nMazos=0;
	if (verificador != -1) {
		//Hallar la cantidad de mazos
		do {
			nMazos++;	
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
	} else {
		cout << "\n\t"; colorTextoFondo("No se encontraron mazos en el directorio", blancoBrillante, rojo); cout << "\n\n";
	}
}
// Función para verificar y crear el archivo de registro si no existe
void verificarEstadistica() {
	string archivoEstadistica = rutaEstadistica("Estadistica Sistema de Flashcards.dat");

	// Verificar si el archivo existe
	ifstream archivo(archivoEstadistica, ios::binary);
	if (!archivo.is_open()) {
		
		// Intentar crear el archivo
		ofstream nuevoArchivo(archivoEstadistica, ios::binary);
		if (!nuevoArchivo.is_open()) {
			cout << "\n\t"; colorTextoFondo("No se pudo crear el archivo de estadísticas...", blancoBrillante, rojo); cout << "\n\n";
			return;
		}

		// Inicializar con datos predeterminados
		eF = {0, 0, 0, 0, 0, 0, 0};
		nuevoArchivo.write(reinterpret_cast<const char*>(&eF), sizeof(eF));
		nuevoArchivo.close();
	} else {
		// Leer los datos del archivo si ya existe
		archivo.read(reinterpret_cast<char*>(&eF), sizeof(eF));
		archivo.close();
	}
	archivo.close();
}
// Función para actualizar el archivo de registro
void actualizarEstadistica(int valor, int campo) {
	verificarEstadistica();

	switch (campo) {
		case 1: eF.mazosCreados += valor; break;
		case 2: eF.mazosEliminados += valor; break;
		case 3: eF.repasosTotales += valor; break;
		case 4: eF.repasosCancelados += valor; break;
		case 5: eF.puntuacion1 += valor; break;
		case 6: eF.puntuacion2 += valor; break;
		case 7: eF.puntuacion3 += valor; break;
		default: cout<<"Campo inválido";
    }
    
	// Guardar los cambios en el archivo
	ofstream actualizarEstadistica(rutaEstadistica("Estadistica Sistema de Flashcards.dat"), ios::binary);
	if (!actualizarEstadistica.is_open()) {
		cout << "\n\t"; colorTextoFondo("No se pudo abrir el archivo de estadísticas", blancoBrillante, rojo); cout << "\n\n";
		return;
	}

	actualizarEstadistica.write(reinterpret_cast<const char*>(&eF), sizeof(eF));
	actualizarEstadistica.close();
}

//Funciones mazos
void crearMazo();
void mostrarMazos();
void renombrarMazo();
void eliminarMazo();
void repasoFlashcards();
void estadisticasFlashcards();

//Funciones cartas
void menuCartas();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();

// Menú de opciones
int main() {
	// Addmite la codificación UTF-8 (caracteres especiales)
	SetConsoleOutputCP(CP_UTF8);
	
	// Crear el directorio o carpeta principal
	CreateDirectory(directorio.c_str(), NULL);

	// Crear la subcarpeta para las estadisticas dentro del directorio principal
	string directorioCompleto = directorio + "\\" + dirEstadisticas;
	if (!CreateDirectoryA(directorioCompleto.c_str(), NULL)) {
		if (GetLastError() != ERROR_ALREADY_EXISTS) {
			cout << "\n\t"; colorTextoFondo("No se pudo crear el directorio de registro...", blancoBrillante, rojo); cout << "\n\n";
		}
	}
	
	// Verificar el archivo para su uso en las diferentes funciones
	verificarEstadistica();
	
	int opcion;
	
	string tituloMazos = "SISTEMA DE FLASHCARDS";
	string menuMazos[8] = {
		"1. Crear mazo",
		"2. Mostrar mazos",
		"3. Renombrar mazo",
		"4. Eliminar mazo",
		"5. Menú de flashcards",
		"6. Repaso de flashcards",
		"7. Estadísticas",
		"\n\tESC. Volver al menú principal ASPE"
	};
	
	do{
        opcion = opcionSeleccionada(menuMazos, tituloMazos, 8);
		
		system("cls");
		
		// Ejecutamos la función correspondiente según la opción seleccionada
		switch (opcion) {
			case 1: {
				crearMazo();
				break;
			}
			case 2: {
				mostrarMazos();
				break;
			}
			case 3: {
				renombrarMazo();
				break;
			}
			case 4: {
				eliminarMazo();
				break;
			}
			case 5: {
				menuCartas();
				break;
			}
			case 6: {
				verificarMazos();
				if (nMazos>0){
					repasoFlashcards();
				}
				break;
			}
			case 7: {
				verificarMazos();
				if (nMazos>0){
					estadisticasFlashcards();
				}
				break;
			}
			case 0: {
				cout << "\n\tVolviendo al menú principal ASPE...\n\n";
				break;
			}
			default: {
				colorTextoFondo("\n\tOpción no válida. Por favor, seleccione una opción válida.\n\n", blancoBrillante, rojo);
				break;
			}
		}
		system("pause");
		system("cls");
	} while (opcion != 0);
	return 0;
}

void menuCartas() {
	verificarMazos();
	if (nMazos>0){
		int opcion;
		
		string tituloMazos = "MENÚ DE FLASHCARDS";
		string menuMazos[6] = {
			"1. Crear flashcards",
			"2. Mostrar flashcards",
			"3. Editar flashcards",
			"4. Eliminar flashcard",
			"5. Repaso flashcard",
			"\n\tESC. Vover al menú Sistema de Flashcards"
		};
		
		do{
			opcion = opcionSeleccionada(menuMazos, tituloMazos, 6);
			
			system("cls");
			
			switch (opcion) {
				case 1: {
					crearCarta();
					
					break;
				}
				case 2: {
					mostrarCartas();
					break;
				}
				case 3: {
					editarCarta();
					break;
				}
				case 4: {
					eliminarCarta();
					break;
				}
				case 5: {
					repasoFlashcards();
					break;
				}
				case 0: {
					cout << "\n\tVolviendo al menú Sistema de flashcards...\n\n";
					break;
				}
				default: {
					cout << "\n\t"; colorTextoFondo("Opción no válida. Por favor, seleccione una opción válida.", blancoBrillante, rojo);
					break;
				}
			}
			system("pause");
			system("cls");
		} while (opcion != 0);	
	}
}

// Funciones CRUD mazos
void crearMazo() {
	string nombreMazo;
	ofstream mazo;
	
	fflush(stdin);
	cout << "\n\n\tNombre del mazo: "; getline(cin, nombreMazo);
	
	// Crea un archivo en una carpeta
	mazo.open(ruta(nombreMazo + ".txt"), ios::out);
	
	if(mazo.fail()) {
		cout << "\n\t"; colorTextoFondo("No se pudo crear el mazo", blancoBrillante, rojo); cout << "\n\n";
	} else {
		cout << "\n\t"; colorTextoFondo("¡Mazo creado correctamente!", blancoBrillante, verde); cout << "\n\n";
		actualizarEstadistica(1,1);
	}
	
	mazo.close();
}

void mostrarMazos() {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	nMazos=0;
	if (verificador != -1) {
		//Hallar la cantidad de mazos
		do {
			nMazos++;	
		} while (_findnext(verificador, &archivo) == 0);
		
		_findclose(verificador);
		
		// Define el vector global nombresMazos
		nombresMazos = new string [nMazos];
		// Almacena en el vector los nombres de los mazos y los muestra
		verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
		
		int contadorMazo=0;
		cout << "\n";
		do {
			nombresMazos[contadorMazo] = archivo.name;
			cout << "\t" << contadorMazo << ' ' << nombresMazos[contadorMazo] << endl;
			contadorMazo++;
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
		cout << "\n";
	} else {
		cout << "\n\t"; colorTextoFondo("No se encontraron mazos en el directorio", blancoBrillante, rojo); cout << "\n\n"; 
	}
}

void renombrarMazo() {
	mostrarMazos();
	
	// Verificar que hayan mazos
	if (nMazos>0){	
		string nuevoNombre;
		// Verificar la entrada correcta del ID
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo que desea renombrar: "; cin >> idMazo;
			if( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() ){
				cout << "\n\t"; colorTextoFondo("ID inválido", blancoBrillante, rojo); cout << "\n\n"; 
			}
		}while( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() );
		
		fflush(stdin);
		cout << "\n\tNuevo nombre del mazo: "; getline(cin, nuevoNombre);
		
		if (rename (ruta(nombresMazos[idMazo]).c_str(), ruta(nuevoNombre + ".txt").c_str() ) != 0) {
	        cout << "\n\t"; colorTextoFondo("Error al renombrar el mazo.", blancoBrillante, rojo); cout << "\n\n";
	    } else {
	    	cout << "\n\t"; colorTextoFondo("¡El nombre del mazo se ha cambiado correctamente!", blancoBrillante, verde); cout << "\n\n";
		}	
	}
}

void eliminarMazo() {
	mostrarMazos();
	
	// Verificar que hayan mazos
	if (nMazos>0){
		// Verificar la entrada correcta del ID
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo que desea eliminar: "; cin >> idMazo;
			if( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() ){
				cout << "\n\t"; colorTextoFondo("ID inválido", blancoBrillante, rojo); cout << "\n\n";
			}
		}while( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() );
		
		
		if (remove( ruta(nombresMazos[idMazo]).c_str() ) != 0) {
	        cout << "\n\t"; colorTextoFondo("Error al eliminar el mazo.", blancoBrillante, rojo); cout << "\n\n";
	    } else {
	    	cout << "\n\t"; colorTextoFondo("¡El mazo se ha eliminado correctamente!", blancoBrillante, verde); cout << "\n\n";
	    	actualizarEstadistica(1,2);
		}
	}
}

// Funciones CRUD cartas
void crearCarta() {
	bool continuar;
	
	mostrarMazos();
	
	// Verificar la entrada correcta del ID
	do{
		cin.clear();
		fflush(stdin);	
		cout << "\tID del mazo donde desea crear las flashcards: "; cin >> idMazo;
		if( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() ){
			cout << "\n\t"; colorTextoFondo("ID inválido", blancoBrillante, rojo); cout << "\n\n";
		}
	}while( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() );
	
	ofstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::app ); // ios::app permite añadir o adjuntar contenido al archivo
	if(mazo.fail()){
		cout << "\n\t"; colorTextoFondo("No se pudo abrir el mazo", blancoBrillante, rojo); cout << "\n\n";
		return;
	}
	
	do {
		system("cls");
		fflush(stdin);
		cout << "\n\tTema: "; getline(cin, tema);
		cout << "\tContenido: "; getline(cin, contenido);
		mazo << "t:: " << tema << endl << "c:: " << contenido << endl << endl;
		cout << "\tDesea agregar más flashcards (Sí = 1) (No = 0): ";
		cin >> continuar;
	} while (continuar);
	
	cout << "\n";
	mazo.close();
}

void mostrarCartas() {
	mostrarMazos();
	
	// Verificar la entrada correcta del ID
	do{
		cin.clear();
		fflush(stdin);	
		cout << "\tID del mazo donde desea mostrar las flashcards: "; cin >> idMazo;
		if( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() ){
			cout << "\n\t"; colorTextoFondo("ID inválido", blancoBrillante, rojo); cout << "\n\n";
		}
	}while( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() );
	
	ifstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::in );
	
	string linea, tema = "", contenido = "";
	idFlashcard = 0;
	
	while( getline(mazo, linea) ){ // Mientras se logre leer una linea en el mazo
		
		// Verifica si la linea esta vacia y la saltea;
		if( linea.empty() == true){
			continue;
		}
		
		// Si encuentra t:: en linea
		if( linea.substr(0,4) == "t:: "){
			tema = linea.substr(4);
			
			// Si encuentra c:: en la siguiente linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				contenido = linea.substr(4);
				
				// Impresion de datos
				cout<<"\n\tID Flashcard: "<<idFlashcard;
				cout<<"\n\tTema: "<<tema;
				cout<<"\n\tContenido: "<<contenido<<endl;
				idFlashcard++;
			}
		}	
	}
	cout << "\n";
	
	//En caso de no encontrar flashcards
	if( idFlashcard == 0 ){
		cout << "\n\t"; colorTextoFondo("No se encontraron cartas en el mazo...", blancoBrillante, rojo); cout << "\n\n";
	}
	
	mazo.close();
}

void editarCarta() {
	mostrarCartas();

	// Comprobar si hay flashcards en el mazo
	ifstream mazoPrueba;
	mazoPrueba.open( ruta(nombresMazos[idMazo]), ios::in);
	if(mazoPrueba.fail()){
		colorTextoFondo("\n\tNo se pudo abrir el mazo\n\n", blancoBrillante, rojo);
		return;
	}	
    
	string lineaPrueba;
	bool sinFlashcards = false;
    
	while (getline(mazoPrueba, lineaPrueba)) {
		if (!lineaPrueba.empty() && lineaPrueba.substr(0, 4) == "t:: ") {
			sinFlashcards = true;
			break;
        }
    }
	mazoPrueba.close();

	if (!sinFlashcards) {
        return;  // Salir de la función si no se encuentran flashcards
	}
	
	// Verificar que el ID sea válido
	do{
		cin.clear();
		fflush(stdin);	
		cout << "\tID de la flashcard que desea actualizar: "; cin >> idFlashcardUsuario;
		if( idFlashcardUsuario > idFlashcard - 1|| idFlashcardUsuario < 0 || cin.fail() ){
			colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
		}
	}while( idFlashcardUsuario > idFlashcard - 1 || idFlashcardUsuario < 0 || cin.fail() );
	
	// Editar una flashcard en caso el mazo tenga contenido
	ifstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::in);
	if(mazo.fail()){
		colorTextoFondo("\n\tNo se pudo abrir el mazo\n\n", blancoBrillante, rojo);
		return;
	}
	
	ofstream temp;
	temp.open( ruta("temp.txt"), ios::out);
	if(temp.fail()){
		colorTextoFondo("\n\tNo se pudo abrir el mazo\n\n", blancoBrillante, rojo);
		return;
	}
	
		
		
	//Bucle para recorrer
	string linea, nuevoTema, nuevoContenido;
	idFlashcard = 0;
	
	while( getline(mazo,linea) ){
		
		// Verifica si la linea esta vacia y la saltea;
		if( linea.empty() == true){
			continue;
		}
		
		// Si encuentra t:: en linea
		if( linea.substr(0,4) == "t:: "){
			
			if (idFlashcard == idFlashcardUsuario) {
				fflush(stdin);
				cout << "\tNuevo tema: "; getline(cin, nuevoTema);
				temp<<"t:: "<<nuevoTema<<endl;
			}else{
				temp << endl << linea <<endl;
			}
			
			// Si encuentra c:: en la linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				
				if (idFlashcard == idFlashcardUsuario) {
					fflush(stdin);
					cout << "\tNuevo contenido: "; getline(cin, nuevoContenido);
					temp << "c:: " << nuevoContenido << endl << endl;
				}else{
					temp << linea << endl <<endl;
				}

				idFlashcard++;
			}
		}	
	}
	
	mazo.close();
	temp.close();
	remove( ruta(nombresMazos[idMazo]).c_str());
	
	//En caso de no encontrar flashcards
	if( idFlashcard == 0 ){
		colorTextoFondo("\n\tNo se encontraron cartas en el mazo...\n\n", blancoBrillante, rojo);
	}else{
		//Conviertiendo temp al nuevo mazo
	    rename( ruta("temp.txt").c_str(), ruta(nombresMazos[idMazo]).c_str());
	    colorTextoFondo("\n\tFlashcard actualizada correctamente.\n\n", blancoBrillante, verde);	
	}
}

void eliminarCarta(){

	mostrarCartas();
	// Comprobar si hay cartas en el mazo
	ifstream mazoPrueba;
	mazoPrueba.open( ruta(nombresMazos[idMazo]), ios::in);
	if(mazoPrueba.fail()){
		cout<<"\n\tNo se pudo abrir el mazo\n\n";
		return;
	}
    
	string lineaPrueba;
	bool sinFlashcards = false;
    
	while (getline(mazoPrueba, lineaPrueba)) {
		if (!lineaPrueba.empty() && lineaPrueba.substr(0, 4) == "t:: ") {
			sinFlashcards = true;
			break;
        }
    }
	mazoPrueba.close();

	if (!sinFlashcards) {
        return;  // Salir de la función si no se encuentran flashcards
	}
	
	// Verificar que el ID sea válido
	do{
		cin.clear();
		fflush(stdin);	
		cout << "\tID de la flashcard que desea actualizar: "; cin >> idFlashcardUsuario;
		if( idFlashcardUsuario > idFlashcard - 1|| idFlashcardUsuario < 0 || cin.fail() ){
			colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
		}
	}while( idFlashcardUsuario > idFlashcard - 1 || idFlashcardUsuario < 0 || cin.fail() );
	
	// Eliminar una tarjeta si el mazo tiene contenido
	ifstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::in);
	
	ofstream temp;
	temp.open( ruta("temp.txt"), ios::out);
	
	
	//Bucle para recorrer
	string linea, nuevoTema, nuevoContenido;
	idFlashcard = 0;
	
	while( getline(mazo,linea) ){
		
		// Verifica si la linea esta vacia y la saltea;
		if( linea.empty() == true){
			continue;
		}
		
		// Si encuentra t:: en linea
		if( linea.substr(0,4) == "t:: "){
			
			if (idFlashcard != idFlashcardUsuario) {
				temp << endl << linea <<endl;
			}
			
			// Si encuentra c:: en la linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				
				if (idFlashcard != idFlashcardUsuario) {
					temp << linea << endl << endl;
				}

				idFlashcard++;
			}
		}	
	}
	
	mazo.close();
	temp.close();
	remove( ruta(nombresMazos[idMazo]).c_str());
	
	//En caso de no encontrar flashcards
	if( idFlashcard == 0 ){
		colorTextoFondo("\n\tNo se encontraron cartas en el mazo...\n\n", blancoBrillante, rojo);
	}else{
		//Conviertiendo temp al nuevo mazo
	    rename( ruta("temp.txt").c_str(), ruta(nombresMazos[idMazo]).c_str());
	    colorTextoFondo("\n\tFlashcard eliminada correctamente.\n\n", blancoBrillante, verde);	
	}
}

void repasoFlashcards() {
	string rpta, linea;
    char puntaje, seguir;
    bool confirmacion;
	
	//Se crea la subcarpeta en el directorio "MAZOS"
	CreateDirectory( rutaRepaso("").c_str(), NULL);
	
	// Verificar si mazoRepaso aun tiene flashcards por repasar y brindar la opcion de cancelar un repaso
	ifstream verificar( rutaRepaso("mazoRepaso.txt") );
	if(verificar.peek() != ifstream::traits_type::eof()){
		verificar.close();
		cout << "\n\t¡Su mazo tiene aún cartas por repasar!";
		cout << "\n\tDesea cancelar el repaso anterior (Esto descartará las flashcards que aún necesitan repaso)";
	    
		int confirmacion;
	    do {
			cin.clear();
			fflush(stdin);
			cout << "\n\n\tIngrese su opción 1 (SÍ) o 0 (NO): ";
			cin.clear();
			cin >> confirmacion;
			if (confirmacion != 0 && confirmacion != 1) {
				colorTextoFondo("\n\n\tOpción inválida. Por favor ingrese 1 (SÍ) o 0 (NO).\n", blancoBrillante, rojo);
			}
		} while (confirmacion != 0 && confirmacion != 1);
		
		if (confirmacion == 1){
			if (remove(rutaRepaso("mazoRepaso.txt").c_str()) == 0) {
				colorTextoFondo("n\n\tEl archivo mazoRepaso.txt se ha eliminado correctamente.\n\n", blancoBrillante, verde);
				actualizarEstadistica(1,4);
			} else {
				colorTextoFondo("\n\n\tNo se pudo eliminar el archivo mazoRepaso.txt.\n\n", blancoBrillante, rojo);
				return;
			}
		} else {
			cout << "\n\tContinuando con el repaso...\n\n";
		}
	}
	
	ifstream mazoRepaso2( rutaRepaso("mazoRepaso.txt") );
	if(mazoRepaso2.peek() == ifstream::traits_type::eof()){
		//Copiar flashcards de mazo a mazo Repaso
		mostrarMazos();
		// Verificar la entrada correcta del ID
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo que desea repasar: "; cin >> idMazo;
			if( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() ){
				cout << "\n\t"; colorTextoFondo("ID inválido", blancoBrillante, rojo); cout << "\n\n"; 
			}
		}while( idMazo > nMazos - 1 || idMazo < 0 || cin.fail() );
    	
		// Comprobar si hay flashcards en el mazo
		ifstream mazoPrueba;
		mazoPrueba.open( ruta(nombresMazos[idMazo]), ios::in);
		if(mazoPrueba.fail()){
			cout << "\n\t"; colorTextoFondo("No se pudo abrir el mazo", blancoBrillante, rojo); cout << "\n\n"; 
			return;
		}
	    
		string lineaPrueba;
		bool sinFlashcards = false;
	    
		while (getline(mazoPrueba, lineaPrueba)) {
			if (!lineaPrueba.empty() && lineaPrueba.substr(0, 4) == "t:: ") {
				sinFlashcards = true;
				break;
	        }
	    }
		mazoPrueba.close();
	
		if (!sinFlashcards) {
			cout << "\n\t"; colorTextoFondo("No se encontraron flashcards en el mazo", blancoBrillante, rojo); cout << "\n\n";
			return;  // Salir de la función si no se encuentran flashcards
		}
    	
    	//Copiar flashcards de mazo a mazo Repaso
    	ifstream mazo ( ruta(nombresMazos[idMazo]) );
		ofstream mazoRepaso2 ( rutaRepaso("mazoRepaso.txt" ) );
		
		while ( getline(mazo, linea) ) {
	        mazoRepaso2 << linea << endl;
	    }
	    actualizarEstadistica(1,3);
	    mazo.close();   
	} else {
		//cout << "\n\tSu mazo tiene aún cartas por repasar...\n";
	}
	
	system("pause");
    mazoRepaso2.close();
    
    //Bucle para recorrer
	bool continuar = true;
	
	while ( continuar ){
		idFlashcard = 0;
		
		//Abriendo mazos para iniciar el bucle
		ifstream mazoRepaso( rutaRepaso("mazoRepaso.txt" ) );
		ofstream temp ( rutaRepaso("temp.txt") );
		
		while( getline(mazoRepaso,linea) ){
			
			// Verifica si la linea esta vacia y la saltea;
			if( linea.empty() == true){
				continue;
			}
			
			// Si encuentra t:: en linea
			if( linea.substr(0,4) == "t:: "){
				
				system("cls");
	            fflush(stdin);
				
				tema = linea.substr(4);
	            cout << "\n\t";
	            colorTexto(tema, blancoBrillante); // Pregunta
	            
	            cout << "\n\n\tTu respuesta:\t"; getline(cin, rpta);
				
				// Si encuentra c:: en la linea
				if( getline(mazoRepaso, linea) && linea.substr(0,4) == "c:: " ){
					
					contenido = linea.substr(4);
	            	cout << "\n\tRespuesta:\t" << contenido; // Respuesta correcta
	            	idFlashcard++;
	            	
	            	// Puntuación
		            do {
		            	cout << "\n\n\tMe faltó(1) Bien(2) Excelente(3)\n";
		                cout << "\n\tPuntaje:\t";
		                cin >> puntaje;
		                if (puntaje != '1' && puntaje != '2' && puntaje != '3') {
		                    cout << "\n\t"; colorTextoFondo("Opción inválida", blancoBrillante, rojo); cout << "\n"; 
		                }
		            } while (puntaje != '1' && puntaje != '2' && puntaje != '3');
				    
		            if (puntaje != '3') {    
						// Mantener la flashcard si la respuesta no fue excelente
		                temp << endl << "t:: "<< tema << endl;
		                temp << "c:: " << contenido << endl << endl;
		                if (puntaje=='1'){
		                	actualizarEstadistica(1,5);
						} else {
							actualizarEstadistica(1,6);
						}
		            }else{
		            	system("cls");
		            	cout << "\n\n\t"; colorTextoFondo("¡Flashcard completada!", blancoBrillante, verde);
		            	actualizarEstadistica(1,7);
					}
				
					do {
				        cout << "\n\n\tSiguiente(1) | Salir(0):\t";
				        cin >> seguir;
				        if (seguir != '0' && seguir != '1') {
				            cout << "\n\t"; colorTextoFondo("Opción inválida", blancoBrillante, rojo); cout << "\n"; 
				        }
				    } while (seguir != '0' && seguir != '1');
				    
				    if (seguir == '0') {
				    	
				    	while ( getline(mazoRepaso, linea) ) {
	        				temp << linea << endl;
	    				}
				    	
				        continuar = false;
				        break;
				    }
				}
			}	
		}
		
		//En caso de no encontrar flashcards
		if( idFlashcard == 0 ){
			continuar = false;
			cout << "\n\t"; colorTextoFondo("No se encontraron cartas en el mazo...", blancoBrillante, rojo); cout << "\n\n"; 
		}
		
		mazoRepaso.close();
		temp.close();
		
		//Conviertiendo temp al nuevo mazo
		remove( rutaRepaso("mazoRepaso.txt").c_str());
		rename( rutaRepaso("temp.txt").c_str(), rutaRepaso("mazoRepaso.txt").c_str());
		
		system("pause");
		system("cls");
    }
    
    cout << "\n\t"; colorTextoFondo("Vale. Hemos terminado el repaso :D", blancoBrillante, verde); cout << "\n\n"; 
}

void estadisticasFlashcards() {
	verificarEstadistica();
	cout << "\n\n\t"; colorTexto("ESTADÍSTICAS DEL SISTEMA DE FLASHCARDS", blancoBrillante);
	cout << "\n\n\tMazos actuales:\t\t"; cout << nMazos;
	cout << "\n\tMazos creados:\t\t"; cout <<eF.mazosCreados;
	cout << "\n\tMazos eliminados:\t"; cout << eF.mazosEliminados;
	cout << "\n\n\tRepasos totales:\t"; cout << eF.repasosTotales;
	cout << "\n\tRepasos completados:\t"; cout << eF.repasosTotales - eF.repasosCancelados;
	cout << "\n\tRepasos cancelados:\t"; cout << eF.repasosCancelados;
	cout << "\n\n\tFlashcards repasadas:\t"; cout << eF.puntuacion1 + eF.puntuacion2 + eF.puntuacion3;
	cout << "\n\tPuntuación 1:\t\t"; cout << eF.puntuacion1;
	cout << "\n\tPuntuación 2:\t\t"; cout << eF.puntuacion2;
	cout << "\n\tPuntuación 3:\t\t"; cout << eF.puntuacion3;
	cout << "\n\n";
}
