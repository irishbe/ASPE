#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "colores.h"

using namespace std;

// Nombre del directorio o carpeta para almacenar los mazos
const string directorio = "Mazos ASPE";
const string dirRepaso = "Repaso";

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

//Funciones mazos
void crearMazo();
void mostrarMazos();
void renombrarMazo();
void eliminarMazo();
void repasoFlashcards();

//Funciones cartas
void menuCartas();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();

int main() {
	// Addmite la codificación UTF-8 (caracteres especiales)
	SetConsoleOutputCP(CP_UTF8);
	
	string opcion;
	
	// Crear el directorio  o carpeta
	CreateDirectory(directorio.c_str(), NULL);
	
	do{
		// Mostramos el menú de opciones del contenedor
		colorTexto("\n\n\tSISTEMA DE FLASHCARDS", blancoBrillante);
        cout << "\n\n\t1. Crear mazo";
        cout << "\n\t2. Mostrar mazos";
        cout << "\n\t3. Renombrar mazo";
        cout << "\n\t4. Eliminar mazo";
        cout << "\n\t5. Menú de flashcards";
        cout << "\n\t6. Repaso de flashcards";
        cout << "\n\t0. Salir";
        
        // Solicitamos la opción al usuario
		fflush(stdin);
		cout << "\n\n\tSeleccione una opción: ";
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
			case '5': {
				menuCartas();
				break;
			}
			case '6': {
				repasoFlashcards();
				break;
			}
			case '0': {
				cout << "\n\tVolviendo al menú principal...\n\n";
				break;
			}
			default: {
				colorTextoFondo("\n\tOpción no válida. Por favor, seleccione una opción válida.\n\n", blancoBrillante, rojo);
				break;
			}
		}
		system("pause");
		system("cls");
	} while (opcion[0] != '0');
	return 0;
}

void menuCartas() {
	int opcion;
	
	do{
		// Mostramos el menú de opciones del contenedor
		colorTexto("\n\n\tMENÚ DE FLASHCARDS", blancoBrillante);
        cout << "\n\n\t1. Crear flashcards";
        cout << "\n\t2. Mostrar flashcards";
        cout << "\n\t3. Editar flashcards";
        cout << "\n\t4. Eliminar flashcard";
        cout << "\n\t5. Repaso flashcard";
        cout << "\n\t0. Salir";
        
        
        // Solicitamos la opción al usuario
		cout << "\n\n\tSeleccione una opción: "; cin >> opcion;
		
		// Ejecutamos la función correspondiente según la opción seleccionada
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
				cout << "\n\tVolviendo al menú de las flashcards...\n\n";
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
	string nuevoNombre;
	
	fflush(stdin);
	cout << "\tID del mazo que desea renombrar: "; cin >> id; // Extrae el nombre del mazo a partir del id
	fflush(stdin);
	cout << "\n\tNuevo nombre del mazo: "; getline(cin, nuevoNombre);
	
	if (rename (ruta(nombresMazos[id]).c_str(), ruta(nuevoNombre + ".txt").c_str() ) != 0) {
        colorTextoFondo("\n\tError al renombrar el mazo.\n\n", blancoBrillante, rojo);
    } else {
    	colorTextoFondo("\n\t¡El nombre del mazo se ha cambiado correctamente!\n\n", blancoBrillante, verde);
	}
}

void eliminarMazo() {
	mostrarMazos();
	
	fflush(stdin);
	cout << "\tID del mazo que desea eliminar: "; cin >> id;
	
	if (remove( ruta(nombresMazos[id]).c_str() ) != 0) {
        colorTextoFondo("\n\tError al eliminar el mazo.\n\n", blancoBrillante, rojo);
    } else {
    	colorTextoFondo("\n\t¡El mazo se ha eliminado correctamente!\n\n", blancoBrillante, verde);
	}
}

void crearCarta() {
	bool continuar;
	
	mostrarMazos();
	
	fflush(stdin);
	cout << "\tID del mazo: "; cin >> idMazo;
	
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
	
	fflush(stdin);
	cout << "\tID del mazo: "; cin >> idMazo;
	
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
		cout<<"\n\tNo se pudo abrir el mazo\n\n";
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
    char pntj, seguir;
	
	//Se crea la subcarpeta en el directorio "MAZOS"
	CreateDirectory( rutaRepaso("").c_str(), NULL);
	ifstream mazoRepaso2( rutaRepaso("mazoRepaso.txt" ) );

	//Verificar si mazoRepaso aun tiene flashcards por repasar, o si esta vacio
	if( mazoRepaso2.peek() == ifstream::traits_type::eof() ){
		//Copiar flashcards de mazo a mazo Repaso
		mostrarMazos();
		fflush(stdin);
    	cout << "\tIngrese el ID del mazo: "; cin >> idMazo;
    	mazoRepaso2.close();
    	
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
	    
	}else{
		cout << "\n\tMazo repaso tiene aun cartas por repasar...\n\n";
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
		                cin >> pntj;
		                if (pntj != '1' && pntj != '2' && pntj != '3') {
		                    colorTextoFondo("\n\tOpción inválida\n", blancoBrillante, rojo);
		                }
		            } while (pntj != '1' && pntj != '2' && pntj != '3');
				    
		            if (pntj != '3') {    
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
		
		// Brinda la opción de salir del repaso
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
