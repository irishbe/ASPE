#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "herramientas.h"

using namespace std;

// Nombre del directorio o carpeta para almacenar los mazos
const string directorio = "Mazos ASPE";
const string dirRepaso = "Repaso";
const string dirEstadistica = "Estadistica Flashcards";

//Variables globales
int n = 0, i, id, idMazo, idCarta;
string tema, contenido, *nombresMazos = nullptr;

//Funciones para generar rutas
string ruta(string nombreArchivo) {
    return (directorio + "/" + nombreArchivo);
}
string rutaRepaso(string nombreArchivo) {
    return (directorio + "/" + dirRepaso + "/" + nombreArchivo);
}
string rutaEstadistica(string nombreArchivo) {
    return (directorio + "/" + dirEstadistica + "/" + nombreArchivo);
}

//Funciones de utilidad
void verificarMazos() {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	n=0;
	if (verificador != -1) {
		//Hallar la cantidad de mazos
		do {
			n++;	
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
	} else {
		colorTextoFondo("\n\tNo se encontraron mazos en el directorio\n\n", blancoBrillante, rojo);
	}
}

//Funciones mazos
void crearMazo();
void mostrarMazos();
void renombrarMazo();
void eliminarMazo();
void repasoFlashcards();
void estadisticaFlashcards();

//Funciones cartas
void menuCartas();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();

int main() {
	// Addmite la codificación UTF-8 (caracteres especiales)
	SetConsoleOutputCP(CP_UTF8);
	
	// Crear el directorio  o carpeta
	CreateDirectory(directorio.c_str(), NULL);
	
	int opcion;
	
	string tituloMazos = "SISTEMA DE FLASHCARDS";
	string menuMazos[8] = {
		"1. Crear mazo",
		"2. Mostrar mazos",
		"3. Renombrar mazo",
		"4. Eliminar mazo",
		"5. Menú de flashcards",
		"6. Repaso de flashcards",
		"7. Estadísticas del Sistema de Flashcards",
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
				if (n>0){
					repasoFlashcards();
				}
				break;
			}
			case 7: {
				estadisticaFlashcards();
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
	if (n>0){
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
					colorTextoFondo("\n\tOpción no válida. Por favor, seleccione una opción válida.\n\n", blancoBrillante, rojo);
					break;
				}
			}
			system("pause");
			system("cls");
		} while (opcion != 0);	
	}
}

void crearMazo() {
	string nombreMazo;
	ofstream mazo;
	
	fflush(stdin);
	cout << "\n\n\tNombre del mazo: "; getline(cin, nombreMazo);
	
	// Crea un archivo en una carpeta
	mazo.open(ruta(nombreMazo + ".txt"), ios::out);
	
	if(mazo.fail()) {
		colorTextoFondo("\n\tNo se pudo crear el mazo\n\n", blancoBrillante, rojo);
	} else {
		colorTextoFondo("\n\t¡Mazo creado correctamente!\n\n", blancoBrillante, verde);
	}
	
	mazo.close();
}

void mostrarMazos() {
	// Almacena la informacion de un archivo
	_finddata_t archivo;
	
	// Crea un verificador que comprueba si hay archivos .txt
	intptr_t verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
	
	// Verifica si la busqueda fue exitosa
	n=0;
	if (verificador != -1) {
		//Hallar la cantidad de mazos
		do {
			n++;	
		} while (_findnext(verificador, &archivo) == 0);
		
		_findclose(verificador);
		
		// Define el vector global nombresMazos
		nombresMazos = new string [n];
		// Almacena en el vector los nombres de los mazos y los muestra
		verificador = _findfirst( (directorio + "//" + "*.txt").c_str() , &archivo);
		
		i=0;
		cout << "\n";
		do {
			nombresMazos[i] = archivo.name;
			cout << "\t" << i << ' ' << nombresMazos[i] << endl;
			i++;
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
		cout << "\n";
	} else {
		colorTextoFondo("\n\tNo se encontraron mazos en el directorio\n\n", blancoBrillante, rojo);
	}
}

void renombrarMazo() {
	mostrarMazos();
	
	// Verificar que hayan mazos
	if (n>0){
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo donde desea mostrar las flashcards: "; cin >> id;
			if( id > n - 1 || id < 0 || cin.fail() ){
				colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
			}
		}while( id > n - 1 || id < 0 || cin.fail() );
		
		string nuevoNombre;
		// Verificar la entrada correcta del ID
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo que desea renombrar: "; cin >> id;
			if( id > n - 1 || id < 0 || cin.fail() ){
				colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
			}
		}while( id > n - 1 || id < 0 || cin.fail() );
		
		fflush(stdin);
		cout << "\n\tNuevo nombre del mazo: "; getline(cin, nuevoNombre);
		
		if (rename (ruta(nombresMazos[id]).c_str(), ruta(nuevoNombre + ".txt").c_str() ) != 0) {
	        colorTextoFondo("\n\tError al renombrar el mazo.\n\n", blancoBrillante, rojo);
	    } else {
	    	colorTextoFondo("\n\t¡El nombre del mazo se ha cambiado correctamente!\n\n", blancoBrillante, verde);
		}	
	}
}

void eliminarMazo() {
	mostrarMazos();
	
	// Verificar que hayan mazos
	if (n>0){
		// Verificar la entrada correcta del ID
		do{
			cin.clear();
			fflush(stdin);	
			cout << "\tID del mazo que desea eliminar: "; cin >> id;
			if( id > n - 1 || id < 0 || cin.fail() ){
				colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
			}
		}while( id > n - 1 || id < 0 || cin.fail() );
		
		
		if (remove( ruta(nombresMazos[id]).c_str() ) != 0) {
	        colorTextoFondo("\n\tError al eliminar el mazo.\n\n", blancoBrillante, rojo);
	    } else {
	    	colorTextoFondo("\n\t¡El mazo se ha eliminado correctamente!\n\n", blancoBrillante, verde);
		}
	}
}

void crearCarta() {
	bool continuar;
	
	mostrarMazos();
	
	// Verificar la entrada correcta del ID
	do{
		cin.clear();
		fflush(stdin);	
		cout << "\tID del mazo donde desea crear las flashcards: "; cin >> id;
		if( id > n - 1 || id < 0 || cin.fail() ){
			colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
		}
	}while( id > n - 1 || id < 0 || cin.fail() );
	
	ofstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::app ); // ios::app permite añadir o adjuntar contenido al archivo
	if(mazo.fail()){
		colorTextoFondo("\n\tNo se pudo abrir el mazo\n\n", blancoBrillante, rojo);
		return;
	}
	
	do {
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
		cout << "\tID del mazo donde desea mostrar las flashcards: "; cin >> id;
		if( id > n - 1 || id < 0 || cin.fail() ){
			colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
		}
	}while( id > n - 1 || id < 0 || cin.fail() );
	
	ifstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::in );
	
	string linea, tema = "", contenido = "";
	id = 0;
	
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
				cout<<"\n\tID Flashcard: "<<id;
				cout<<"\n\tTema: "<<tema;
				cout<<"\n\tContenido: "<<contenido<<endl;
				id++;
			}
		}	
	}
	cout << "\n";
	
	//En caso de no encontrar flashcards
	if( id == 0 ){
		colorTextoFondo("\tNo se encontraron cartas en el mazo...\n\n", blancoBrillante, rojo);
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
	
	// Editar una flashcard en caso el mazo tenga contenido
	fflush(stdin);
	cout << "\tID de la flashcard que desea actualizar: "; cin >> idCarta; 
	
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
	id = 0;
	
	while( getline(mazo,linea) ){
		
		// Verifica si la linea esta vacia y la saltea;
		if( linea.empty() == true){
			continue;
		}
		
		// Si encuentra t:: en linea
		if( linea.substr(0,4) == "t:: "){
			
			if (id == idCarta) {
				fflush(stdin);
				cout << "\tNuevo tema: "; getline(cin, nuevoTema);
				temp<<"t:: "<<nuevoTema<<endl;
			}else{
				temp << endl << linea <<endl;
			}
			
			// Si encuentra c:: en la linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				
				if (id == idCarta) {
					fflush(stdin);
					cout << "\tNuevo contenido: "; getline(cin, nuevoContenido);
					temp << "c:: " << nuevoContenido << endl << endl;
				}else{
					temp << linea << endl <<endl;
				}

				id++;
			}
		}	
	}
	
	mazo.close();
	temp.close();
	remove( ruta(nombresMazos[idMazo]).c_str());
	
	//En caso de no encontrar flashcards
	if( id == 0 ){
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
	
	// Eliminar una tarjeta si el mazo tiene contenido
	fflush(stdin);
	cout << "\tID de la flashcard que desea eliminar: "; cin >> idCarta; // Extrae el nombre del mazo a partir del id
	
	ifstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::in);
	
	ofstream temp;
	temp.open( ruta("temp.txt"), ios::out);
	
	
	//Bucle para recorrer
	string linea, nuevoTema, nuevoContenido;
	id = 0;
	
	while( getline(mazo,linea) ){
		
		// Verifica si la linea esta vacia y la saltea;
		if( linea.empty() == true){
			continue;
		}
		
		// Si encuentra t:: en linea
		if( linea.substr(0,4) == "t:: "){
			
			if (id != idCarta) {
				temp << endl << linea <<endl;
			}
			
			// Si encuentra c:: en la linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				
				if (id != idCarta) {
					temp << linea << endl << endl;
				}

				id++;
			}
		}	
	}
	
	mazo.close();
	temp.close();
	remove( ruta(nombresMazos[idMazo]).c_str());
	
	//En caso de no encontrar flashcards
	if( id == 0 ){
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
		cout << "\n\tSu mazo tiene aún cartas por repasar...\n";
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
				cout << "\n\n\tEl archivo mazoRepaso.txt se ha eliminado correctamente.\n\n";
			} else {
				cout << "\n\n\tNo se pudo eliminar el archivo mazoRepaso.txt.\n\n";
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
			cout << "\tID del mazo que desea repasar: "; cin >> id;
			if( id > n - 1 || id < 0 || cin.fail() ){
				colorTextoFondo("\n\tID inválido\n\n", blancoBrillante, rojo);
			}
		}while( id > n - 1 || id < 0 || cin.fail() );
    	
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
			colorTextoFondo("\n\tNo se encontraron flashcards en el mazo\n\n", blancoBrillante, rojo);
			return;  // Salir de la función si no se encuentran flashcards
		}
    	
    	//Copiar flashcards de mazo a mazo Repaso
    	ifstream mazo ( ruta(nombresMazos[idMazo]) );
		ofstream mazoRepaso2 ( rutaRepaso("mazoRepaso.txt" ) );
		
		while ( getline(mazo, linea) ) {
	        mazoRepaso2 << linea << endl;
	    }
	    mazo.close();   
	} else {
		//cout << "\n\tSu mazo tiene aún cartas por repasar...\n";
	}
	
	system("pause");
    mazoRepaso2.close();
    
    //Bucle para recorrer
	bool continuar = true;
	
	while ( continuar ){
		id = 0;
		
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
	            	id++;
	            	
	            	// Puntuación
		            do {
		            	cout << "\n\n\tMe faltó(1) Bien(2) Excelente(3)\n";
		                cout << "\n\tPuntaje:\t";
		                cin >> puntaje;
		                if (puntaje != '1' && puntaje != '2' && puntaje != '3') {
		                    colorTextoFondo("\n\tOpción inválida\n", blancoBrillante, rojo);
		                }
		            } while (puntaje != '1' && puntaje != '2' && puntaje != '3');
				    
		            if (puntaje != '3') {    
						// Mantener la flashcard si la respuesta no fue excelente
		                temp << endl << "t:: "<< tema << endl;
		                temp << "c:: " << contenido << endl << endl;
		            }else{
		            	system("cls");
		            	colorTextoFondo("\n\n\t¡Flashcard completada!", blancoBrillante, verde);
					}
				
					do {
				        cout << "\n\n\tSiguiente(1) | Salir(0):\t";
				        cin >> seguir;
				        if (seguir != '0' && seguir != '1') {
				            colorTextoFondo("\n\tOpción inválida\n", blancoBrillante, rojo);
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
		if( id == 0 ){
			continuar = false;
			colorTextoFondo("\n\tNo se encontraron cartas en el mazo...\n\n", blancoBrillante, rojo);
		}
		
		mazoRepaso.close();
		temp.close();
		
		//Conviertiendo temp al nuevo mazo
		remove( rutaRepaso("mazoRepaso.txt").c_str());
		rename( rutaRepaso("temp.txt").c_str(), rutaRepaso("mazoRepaso.txt").c_str());
		
		system("pause");
		system("cls");
    }
    
    colorTextoFondo("\n\tVale. Hemos terminado el repaso :D\n\n", blancoBrillante, verde);
}

void estadisticaFlashcards() {
	/*rutaEstadistica("Estadistica Sistema de Flashcards");
	
	cout << "ANÁLISIS DE MAZOS";
	cout << "Mazos creados: ";
	cout << "Mazos creados:			(n)									100%";
	cout << "Repasos completados:	(repasoTotal - repasoCancelado)		(rT-rC)/rT %";
	cout << "Repasos cancelados:	(repasoCancelado)					     rC/rT %";
	
	cout << "ANÁLISIS DE FLASHCARDS";
	cout << "Repasos totales		RT=P1+P2+P3		100% - Borrar";
	cout << "Puntuación 1			123				P1/RT";
	cout << "Puntuación 2			123				P2/RT";
	cout << "Puntuación 3			123				P3/RT";
	cout << "";*/
}
