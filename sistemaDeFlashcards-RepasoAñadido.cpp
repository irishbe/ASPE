#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <direct.h>

using namespace std;

string tema, contenido;

// Nombre del directorio o carpeta
const string directorio = "Sistema de Flashcards";
const string directorioRepasos = "Sistema de Flashcards/Repasos";


int n = 0, i, id;

string* nombresMazos = nullptr;

string ruta(string nombreArchivo) {
    return (directorio + "/" + nombreArchivo);
}
string ruta2(string nombreArchivo) {
    size_t pos = nombreArchivo.find_last_of(".");
    
    if (pos != string::npos) {
        nombreArchivo = nombreArchivo.substr(0, pos);
    }

    return (directorioRepasos + "/" + nombreArchivo + "repaso.txt");
}

void menuCartas();
void crearMazo();
void mostrarMazos(bool soloLectura);
void renombrarMazo();
void eliminarMazo();
void crearCarta();
void mostrarCartas();
void editarCarta();
void eliminarCarta();
void repasoFlashcards();

int main() {
    string opcion;

    // Crear el directorio o carpeta
    if (_mkdir(directorio.c_str())) {
        cout << "Ha ocurrido un error en la creacion de la carpeta"<<endl;
    }
    			
    // Crear la carpeta donde se guardaran los repasos
    if (_mkdir(directorioRepasos.c_str())) {
    	cout << "Ha ocurrido un error en la creacion de la carpeta de repasos";
	}

    do {
        // Mostramos el menú de opciones del contenedor
        cout << "\nCONTENEDOR DE FLASHCARDS\n";
        cout << "\nMenu de opciones:\n";
        cout << "1. Crear mazo\n";
        cout << "2. Mostrar mazos\n";
        cout << "3. Renombrar mazo\n";
        cout << "4. Eliminar mazo\n";
        cout << "5. Repasar flashcards\n"; // Nueva opción para repasar
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
                mostrarMazos(false);
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
                repasoFlashcards(); // Llamada a la función de repaso
                break;
            }
            case '0': {
                cout << "Saliendo del programa..." << endl;
                system("pause");
                break;
            }
            default: {
                cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
                system("pause");
                break;
            }
        }
        system("cls");
    } while (opcion[0] != '0');
}

void menuCartas() {
    int opcion;

    do {
        // Mostramos el menú de opciones del contenedor
        cout << "\nFLASHCARDS\n";
        cout << "\nMenu de opciones:\n";
        cout << "1. Crear flashcards\n";
        cout << "2. Mostrar flashcards\n";
        cout << "3. Editar flashcards\n";
        cout << "4. Eliminar flashcard\n";
        cout << "0. Salir\n";

        // Solicitamos la opción al usuario
        cout << "Seleccione una opción: "; cin >> opcion;

        // Ejecutamos la función correspondiente según la opción seleccionada
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
            case 0:{
            	
				break;
			}
            default: {
                cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
                system("pause");
                break;
            }
        }
    } while (opcion != 0);
}

void crearMazo() {
    string nombreMazo;
    ofstream mazo;

    fflush(stdin);
    cout << "Nombre del mazo: "; getline(cin, nombreMazo);

    // Crea un archivo en una carpeta
    mazo.open(ruta(nombreMazo + ".txt"), ios::out);

    if (mazo.fail()) {
        cout << "No se pudo crear el mazo" << endl;
    }

    mazo.close();
}

void mostrarMazos(bool soloLectura) {
    // Almacena la informacion de un archivo
    _finddata_t archivo;

    // Crea un verificador que comprueba si hay archivos .txt
    intptr_t verificador = _findfirst((directorio + "//" + "*.txt").c_str(), &archivo);

    // Verifica si la busqueda fue exitosa
    if (verificador != -1) {
        // Hallar la cantidad de mazos
        do {
            n++;
        } while (_findnext(verificador, &archivo) == 0);

        _findclose(verificador);

        // Define el vector global nombresMazos
        nombresMazos = new string[n];
        // Almacena en el vector los nombres de los mazos y los muestra
        verificador = _findfirst((directorio + "//" + "*.txt").c_str(), &archivo);

        i = 0;
        do {
            nombresMazos[i] = archivo.name;
            cout << i << ' ' << nombresMazos[i] << endl;
            i++;
        } while (_findnext(verificador, &archivo) == 0);
        _findclose(verificador);

        if (soloLectura == false) {
            menuCartas();
        }
    } else {
        cout << "No se encontraron mazos en el directorio" << endl;
    }
}

void renombrarMazo() {
    mostrarMazos(true);
    string nuevoNombre;

    fflush(stdin);
    cout << "ID del mazo que desea renombrar: "; cin >> id;
    // Extrae el nombre del mazo a partir del id
    fflush(stdin);
    cout << "Nuevo nombre del mazo: "; getline(cin, nuevoNombre);

    if (rename(ruta(nombresMazos[id]).c_str(), ruta(nuevoNombre + ".txt").c_str()) != 0) {
        cout << "Error al renombrar el mazo." << endl;
    } else {
        cout << "El nombre del mazo se ha cambiado correctamente" << endl;
    }
    system("pause");
}

void eliminarMazo() {
    mostrarMazos(true);
    int id;

    fflush(stdin);
    cout << "ID del mazo que desea eliminar: "; cin >> id;

    if (remove(ruta(nombresMazos[id]).c_str()) != 0) {
        cout << "Error al eliminar el mazo." << endl;
    } else {
        cout << "El mazo se ha eliminado correctamente" << endl;
    }
}

void crearCarta() {
    bool continuar;

	system("cls");
    mostrarMazos(true);

    fflush(stdin);
    cout << "ID del mazo: "; cin >> id;

    ofstream mazo;
    mazo.open(ruta(nombresMazos[id]), ios::app); // ios::app permite añadir o adjuntar contenido al archivo

    if (mazo.fail()) {
        cout << "No se pudo abrir el mazo" << endl;
        return;
    }

    do {
        fflush(stdin);
        cout << "Tema: "; getline(cin, tema);
        cout << "Contenido: "; getline(cin, contenido);
        mazo << "t:: " << tema << endl << "c:: " << contenido << endl;
        cout << "Desea agregar más flashcards (Sí = 1) (No = 0): ";
        cin >> continuar;
    } while (continuar);

    mazo.close();
}

void mostrarCartas() {
	
	system("cls");
    mostrarMazos(true);

    fflush(stdin);
    cout << "ID del mazo: "; cin >> id;

    ifstream mazo;
    mazo.open(ruta(nombresMazos[id]), ios::in);

    string linea, tema = "", contenido = "";
    id = 0;

    while (getline(mazo, linea)) {
        // Verifica si la linea esta vacia y la saltea;
        if (linea.empty() == true) {
            continue;
        }

        // Si encuentra t:: en linea
        if (linea.substr(0, 3) == "t::") {
            tema = linea.substr(3);

            // Si encuentra c:: en la linea
            if (getline(mazo, linea) && linea.substr(0, 3) == "c::") {
                contenido = linea.substr(3);

                // Impresion de datos, r:(Se debe mejorar con gotoxy)
                cout << "\nID Flashcard: " << id << endl;
                cout << "Tema:" << tema << endl;
                cout << "Contenido:" << contenido << endl;
                id++;
            }
        }
    }

    // En caso de no encontrar flashcards
    if (id == 0) {
        cout << "\nNo se encontraron cartas en el mazo..." << endl;
    }

    mazo.close();
    cout<<endl; system("pause");
    system("cls");
}

void editarCarta() {
    // Implementar función de editar carta si es necesario
}

void eliminarCarta() {
    // Implementar función de eliminar carta si es necesario
}

void repasoFlashcards() {
	
	int id;
    string rpta;
    char pntj, seguir;
    vector<pair<string, string>> flashcards; // Almacena pares de pregunta-respuesta
    vector<pair<string, string>> repaso; // Almacena flashcards que necesitan repaso

    mostrarMazos(true);

    cout <<endl<<endl<< "Ingrese el ID del mazo: ";
    cin >> id; fflush(stdin);

    fstream archivo_repaso;
    archivo_repaso.open(ruta2(nombresMazos[id]), ios::in);

    // Cargar flashcards del archivo de repaso si existe
    if (archivo_repaso.is_open()) {
        string pregunta, respuesta;
        while (getline(archivo_repaso, pregunta) && getline(archivo_repaso, respuesta)) {
            flashcards.emplace_back(pregunta, respuesta);
        }
        archivo_repaso.close();
    }

    // Si el archivo de repaso está vacío, cargar el archivo original
    if (flashcards.empty()) {
        ifstream archivop;
        archivop.open(ruta(nombresMazos[id]), ios::in);
        if (!archivop.is_open()) {
            cout << "No se pudo abrir el archivo original" << endl;
            return;
        }
        string pregunta, respuesta;
        while (getline(archivop, pregunta) && getline(archivop, respuesta)) {
            flashcards.emplace_back(pregunta, respuesta);
        }
        archivop.close();
    }

    bool continuar = true;
    while (continuar) {
        repaso.clear(); // Limpiar las tarjetas de repaso antes de iniciar

        for (auto it = flashcards.begin(); it != flashcards.end();) {
            system("cls");
            cout << it->first << endl << endl; // Pregunta
            cout << "Tu respuesta--> ";
            getline(cin, rpta);

            cout << endl << "Respuesta-->" << it->second << endl << endl << endl; // Respuesta correcta
            cout << "\tMe falto(1) Bien(2) Excelente(3)" << endl;

            // Puntuación
            do {
                cout << "Puntue--> ";
                cin >> pntj;
                if (pntj != '1' && pntj != '2' && pntj != '3') {
                    cout << " x Opcion invalida" << endl;
                }
            } while (pntj != '1' && pntj != '2' && pntj != '3');
            cin.ignore();

            if (pntj == '3') {
                // Eliminar la flashcard si la respuesta fue excelente
                it = flashcards.erase(it);
            } else {
                // Mantener la flashcard si la respuesta no fue excelente
                repaso.emplace_back(it->first, it->second);
                ++it;
            }

            // Brinda la opción de salir del repaso
            do {
                cout << endl << "Siguiente(1) | Salir(0) --> ";
                cin >> seguir;
                if (seguir != '0' && seguir != '1') {
                    cout << "x Invalido" << endl;
                }
            } while (seguir != '0' && seguir != '1');
            cin.ignore();

            if (seguir == '0') {
                continuar = false;
                break;
            }
        }

        // Si quedan tarjetas por repasar, se moveran de repaso a flashcards
        if (!repaso.empty()) {
            flashcards = repaso;
        } else {
            continuar = false;
        }

        // Actualizar archivo de repaso
        archivo_repaso.open(ruta2(nombresMazos[id]), ios::out | ios::trunc);
        for (const auto& card : flashcards) {
            archivo_repaso << card.first << endl << card.second << endl;
        }
        archivo_repaso.close();

        system("cls");
    }

    cout << "\t\tVale. Hemos terminado el repaso :)" << endl<<endl;
    system("pause");
}


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
	
	 //Abrimos el archivo en modo añadir
	
	
	
	cout<<"Digite el texto que quiere añadir: ";
	getline(cin, texto);
	
	archivo<<texto<<endl;
	
	archivo.close(); //Cerramos el archivo
}