#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Nombre del directorio o carpeta para almacenar los mazos
const string directorio = "Mazos ASPE";
const string dirRepaso = "Repaso";

//Variables globales
int idMazo, idCarta;
string tema, contenido, *nombresMazos = nullptr;

//Funciones para generar rutas
string ruta(string nombreArchivo) {
    return (directorio + "/" + nombreArchivo);
}
string rutaRepaso(string nombreArchivo) {
    return (directorio + "/" + dirRepaso + "/" + nombreArchivo);
}

//CPP COMO MODULO
void SistemaDeFlashcards();

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

void SistemaDeFlashcards() {
	// Addmite la codificación UTF-8 (caracteres especiales, emojis y otros símbolos)
	SetConsoleOutputCP(CP_UTF8);
	
	string opcion;
	
	// Crear el directorio  o carpeta
	CreateDirectory(directorio.c_str(), NULL);
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nCONTENEDOR DE FLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Crear mazo\n";
        cout << "2. Mostrar mazos\n";
        cout << "3. Renombrar mazo\n";
        cout << "4. Eliminar mazo\n";
        cout << "5. Menú flashcards\n";
        cout << "6. Repaso flashcards\n";
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
			case '5': {
				menuCartas();
				break;
			}
			case '6': {
				repasoFlashcards();
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
		system("pause");
		system("cls");
	} while (opcion[0] != '0');
}

void menuCartas() {
	int opcion;
	
	do{
		// Mostramos el menú de opciones del contenedor
		cout << "\nFLASHCARDS\n";
		cout << "\nMenú de opciones:\n";
        cout << "1. Crear flashcards\n";
        cout << "2. Mostrar flashcards\n";
        cout << "3. Editar flashcards\n";
        cout << "4. Eliminar flashcard\n";
        cout << "5. Repaso flashcard\n";
        cout << "0. Salir\n";
        
        
        // Solicitamos la opción al usuario
		cout << "Seleccione una opción: "; cin >> opcion;
		
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
				break;
			}
			default: {
				cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
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
	cout << "Nombre del mazo: "; getline(cin, nombreMazo);
	
	// Crea un archivo en una carpeta
	mazo.open(ruta(nombreMazo + ".txt"), ios::out);
	
	if(mazo.fail()) {
		cout << "No se pudo crear el mazo" << endl;
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
		do {
			nombresMazos[i] = archivo.name;
			cout << i << ' ' << nombresMazos[i] << endl;
			i++;
		} while (_findnext(verificador, &archivo) == 0);
		_findclose(verificador);
		
	} else {
		cout << "No se encontraron mazos en el directorio" << endl;
	}
}

void renombrarMazo() {
	mostrarMazos();
	string nuevoNombre;
	
	fflush(stdin);
	cout << "ID del mazo que desea renombrar: "; cin >> id; // Extrae el nombre del mazo a partir del id
	fflush(stdin);
	cout << "Nuevo nombre del mazo: "; getline(cin, nuevoNombre);
	
	if (rename (ruta(nombresMazos[id]).c_str(), ruta(nuevoNombre + ".txt").c_str() ) != 0) {
        cout << "Error al renombrar el mazo." << endl;
    } else {
    	cout << "El nombre del mazo se ha cambiado correctamente" << endl;
	}
}

void eliminarMazo() {
	mostrarMazos();
	
	fflush(stdin);
	cout << "ID del mazo que desea eliminar: "; cin >> id;
	
	if (remove( ruta(nombresMazos[id]).c_str() ) != 0) {
        cout << "Error al eliminar el mazo." << endl;
    } else {
    	cout << "El mazo se ha eliminado correctamente" << endl;
	}
}

void crearCarta() {
	bool continuar;
	
	mostrarMazos();
	
	fflush(stdin);
	cout << "ID del mazo: "; cin >> idMazo;
	
	ofstream mazo;
	mazo.open( ruta(nombresMazos[idMazo]), ios::app ); // ios::app permite añadir o adjuntar contenido al archivo
	
	if(mazo.fail()){
		cout<<"No se pudo abrir el mazo"<<endl;
		return;
	}
	
	do {
		fflush(stdin);
		cout << "\nTema: "; getline(cin, tema);
		cout << "Contenido: "; getline(cin, contenido);
		mazo << "t:: " << tema << endl << "c:: " << contenido << endl << endl;
		cout << "Desea agregar más flashcards (Sí = 1) (No = 0): ";
		cin >> continuar;
	} while (continuar);
	
	mazo.close();
}

void mostrarCartas() {
	mostrarMazos();
	
	fflush(stdin);
	cout << "ID del mazo: "; cin >> idMazo;
	
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
				cout<<"\nID Flashcard: "<<id<<endl;
				cout<<"Tema: "<<tema<<endl;
				cout<<"Contenido: "<<contenido<<endl;
				id++;
			}
		}	
	}
	
	//En caso de no encontrar flashcards
	if( id == 0 ){
		cout << "\nNo se encontraron cartas en el mazo..." << endl << endl;
	}
	
	mazo.close();
}

void editarCarta() {
	mostrarCartas();
	
	fflush(stdin);
	cout << "\nID de la flashcard que desea actualizar: "; cin >> idCarta; 
	
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
			
			if (id == idCarta) {
				fflush(stdin);
				cout << "Nuevo tema: "; getline(cin, nuevoTema);
				temp<<"t:: "<<nuevoTema<<endl;
			}else{
				temp << endl << linea <<endl;
			}
			
			// Si encuentra c:: en la linea
			if( getline(mazo, linea) && linea.substr(0,4) == "c:: " ){
				
				if (id == idCarta) {
					fflush(stdin);
					cout << "Nuevo contenido: "; getline(cin, nuevoContenido);
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
		cout<<"\nNo se encontraron cartas en el mazo..."<<endl<<endl;
	}else{
		//Conviertiendo temp al nuevo mazo
	    rename( ruta("temp.txt").c_str(), ruta(nombresMazos[idMazo]).c_str());
	    cout << "\nFlashcard actualizada correctamente." << endl<<endl;		
	}
}

void eliminarCarta(){	
	mostrarCartas();
	fflush(stdin);
	cout << "\nID de la flashcard que desea eliminar"; cin >> idCarta; // Extrae el nombre del mazo a partir del id
	
	
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
		cout<<"\nNo se encontraron cartas en el mazo..."<<endl<<endl;
	}else{
		//Conviertiendo temp al nuevo mazo
	    rename( ruta("temp.txt").c_str(), ruta(nombresMazos[idMazo]).c_str());
	    cout << "\nFlashcard eliminada correctamente." << endl << endl;		
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
    	cout << "\n\nIngrese el ID del mazo: "; cin >> id;
    	mazoRepaso2.close();
    	
    	//Copiar flashcards de mazo a mazo Repaso
    	ifstream mazo ( ruta(nombresMazos[id]) );
		ofstream mazoRepaso2 ( rutaRepaso("mazoRepaso.txt" ) );
		
		while ( getline(mazo, linea) ) {
	        mazoRepaso2 << linea << endl;
	    }
	    mazo.close();
	    
	}else{
		cout<<"\nMazo repaso tiene aun cartas por repasar..."<<endl<<endl;
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
	            cout << tema << endl << endl; // Pregunta
	            
	            cout << "Tu respuesta--> "; getline(cin, rpta);
				
				// Si encuentra c:: en la linea
				if( getline(mazoRepaso, linea) && linea.substr(0,4) == "c:: " ){
					
					contenido = linea.substr(4);
	            	cout << "\nRespuesta--> " << contenido << endl << endl; // Respuesta correcta
	            	cout << "\n\tMe falto(1) Bien(2) Excelente(3)" << endl;
	            	
	            	id++;
	            	
	            	// Puntuación
		            do {
		                cout << "Puntue--> ";
		                cin >> pntj;
		                if (pntj != '1' && pntj != '2' && pntj != '3') {
		                    cout << " x Opcion invalida" << endl;
		                }
		            } while (pntj != '1' && pntj != '2' && pntj != '3');
				    
		            if (pntj != '3') {    
						// Mantener la flashcard si la respuesta no fue excelente
		                temp << endl << "t:: "<< tema << endl;
		                temp << "c:: " << contenido << endl << endl;
		            }else{
		            	cout << "\n\nFlashcard completada!." << endl << endl;
					}
				
				
					do {
				        cout << endl << "Siguiente(1) | Salir(0) --> ";
				        cin >> seguir;
				        if (seguir != '0' && seguir != '1') {
				            cout << "x Invalido" << endl;
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
			cout<<"\nNo se encontraron cartas en el mazo..."<<endl<<endl;
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
    
    cout << "\t\tVale. Hemos terminado el repaso :)" << endl<<endl;
}