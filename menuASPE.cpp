#include <iostream>
#include "Modulos ASPE/AccesoModulosAspe.h"

using namespace std;
string *listaUsuarios = nullptr;

void crearUsuario();
int seleccionarUsuario();
void ingresarUsuario();
void renombrarUsuario();
void eliminarUsuario();
void eliminarDirectoriosDeDirectorios(string nombreDirectorio);

int main(){
	gotoxy(10,5);
	colorTexto(
	"\n\t\t       d8888  .d8888b.  8888888b.  8888888888"
	"\n\t\t      d88888 d88P  Y88b 888   Y88b 888"
	"\n\t\t     d88P888 Y88b.      888    888 888"       
	"\n\t\t    d88P 888  Y888b.    888   d88P 8888888"    
	"\n\t\t   d88P  888     Y88b.  8888888P   888"       
	"\n\t\t  d88P   888       888  888        888"        
	"\n\t\t d8888888888 Y88b  d88P 888        888"        
	"\n\t\td88P     888  Y8888P    888        8888888888\n", blancoBrillante);
	
	colorTexto("\n\n\t\tBienvenido a la Aplicacion de Seguimiento del Progreso Estudiantil (ASPE)", blancoBrillante);
    colorTexto("\n\n\t\tPresione cualquier tecla para continuar...", amarilloClaro);
	ocultarCursor(); _getch(); system("cls");
	
    int opc;
    string opcionesUsuarioes[5] = {
        "1. Crear nuevo Usuario ", 
        "2. Ingresar a un Usuario", 
        "3. Renombrar Usuario",
        "4. Eliminar Usuario",
        "0. Salir"
    };
    
    do{
        opc = opcionSeleccionada(opcionesUsuarioes, "MENU DE UsuarioES", 5);
        
        system("cls");
        switch(opc){
            case 1: crearUsuario(); break;
            case 2: ingresarUsuario(); break;
            case 3: renombrarUsuario(); break;
            case 4: eliminarUsuario(); break;
            case 0: colorTexto("\n\tSaliendo... \n\tMuchas gracias por utilizar ASPE\n", amarilloClaro);
        }
        ocultarCursor(); _getch(); system("cls");
        
    }while(opc != 0);
    
    return 0;
}

void crearUsuario(){
    string usuario, periodoAcademico;
    
    colorTexto("\n\t> Creando un nuevo usuario\n", blancoBrillante);
    
	fflush(stdin);
	cout<<"\n\tUsuario: "; getline(cin, usuario);
    fflush(stdin);
	cout<<"\n\tNombre del periodo academico: "; getline(cin, periodoAcademico);
    
    CreateDirectory( (usuario + " - " + periodoAcademico).c_str(), NULL);
    colorTextoFondo("\n\tUsuario creado exitosamente!\n", blancoBrillante, verde);
}

int seleccionarUsuario(){
    WIN32_FIND_DATA archivo;
    HANDLE iterador = FindFirstFile("*", &archivo);
    int cantUsuarioes = 0, i=0, j=0;
    
    //Contabilizar la cantidad de Usuarioes
	do{
		if(iterador == INVALID_HANDLE_VALUE){
			colorTextoFondo("Error al abrir el Usuario seleccionado", blancoBrillante, rojo);
		}else if( archivo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && iterador != INVALID_HANDLE_VALUE){
			string nombre = archivo.cFileName;
			if(nombre != "." && nombre != ".." && nombre != "Modulos ASPE" && nombre != "Programas Independientes"){
				cantUsuarioes++;
			}
		}
	}while (FindNextFile(iterador, &archivo) != 0 && iterador != INVALID_HANDLE_VALUE);
	FindClose(iterador);
	
	//Se llena el vector con los nombres de los Usuarioes
	iterador = FindFirstFile("*", &archivo);
	listaUsuarios = new string [cantUsuarioes+1];
	    	
	do{
		if(iterador == INVALID_HANDLE_VALUE){
			colorTextoFondo("Error al abrir el Usuario seleccionado", blancoBrillante, rojo);
		}else if( archivo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && iterador != INVALID_HANDLE_VALUE){
			string nombre = archivo.cFileName;
				
			if(nombre != "." && nombre != ".." && nombre != "Modulos ASPE" && nombre != "Programas Independientes"){
				listaUsuarios[i] = archivo.cFileName; i++;
			}
		}	
	}while (FindNextFile(iterador, &archivo) != 0);
	
	listaUsuarios[i] = "CANCELAR";
	FindClose(iterador);
	  
	return opcionSeleccionada(listaUsuarios, "> LISTADO DE UsuarioES", cantUsuarioes+1);
}

void ingresarUsuario(){
	int idUsuario = seleccionarUsuario();
	
	if(idUsuario != 0){
		idUsuario--;
		
	    SetCurrentDirectory(listaUsuarios[idUsuario].c_str());
	    AccesoModulosASPE(listaUsuarios[idUsuario]);
	    SetCurrentDirectory("..");
	}else{
		colorTexto("\n\tVolviendo al menu...", amarilloClaro);
	}
}

void renombrarUsuario(){
	int idUsuario = seleccionarUsuario();
	
	if(idUsuario != 0){
		idUsuario--;
		
		string nuevoNombre, nuevoPeriodoAcademico, antiguoNombre = listaUsuarios[idUsuario];
		
		fflush(stdin);
		cout<<"\n\tNuevo Usuario: "; getline(cin, nuevoNombre);
		fflush(stdin);
		cout<<"\n\tNuevo nombre del periodo academico: "; getline(cin, nuevoPeriodoAcademico);
			
		 
		if( MoveFile(antiguoNombre.c_str(), (nuevoNombre + " - " + nuevoPeriodoAcademico).c_str() ) ){
			colorTextoFondo("\n\tUsuario renombrado correctamente!\n", blancoBrillante, verde);
		}else{
			colorTextoFondo("\n\tHubo un error al renombrar el Usuario...\n", blancoBrillante, rojo);
		}
	}else{
		colorTexto("\n\tVolviendo al menu...", amarilloClaro);
	}
}

void eliminarUsuario(){
	int idUsuario = seleccionarUsuario();
	
	if(idUsuario != 0){
		idUsuario--;
		 
		if( RemoveDirectory( listaUsuarios[idUsuario].c_str()) ){
			colorTextoFondo("\n\tUsuario eliminado correctamente!\n", blancoBrillante, verde);
		}else{
			colorTextoFondo("\n\tEste registro de usuario cuenta con archivos dentro...\n", blancoBrillante, rojo);
			
			bool confirmar;
			cout<<"\n\tEsta seguro de querer eliminarlo? (1: Si | 0: No): "; cin>>confirmar;
				
    		if(confirmar==1){
				eliminarDirectoriosDeDirectorios( listaUsuarios[idUsuario] );
				colorTextoFondo("\n\tUsuario eliminado correctamente!\n", blancoBrillante, verde);
			}else{
				colorTexto("\n\n\tVolviendo al menu...", amarilloClaro);
			}
		}
	}else{
		colorTexto("\n\tVolviendo al menu...", amarilloClaro);
	}
}

void eliminarDirectoriosDeDirectorios(string nombreDirectorio){
	WIN32_FIND_DATA archivo;
	HANDLE iterador = FindFirstFile( (nombreDirectorio + "\\*").c_str(), &archivo);
	
	do{
		string nombreArchivo = archivo.cFileName;
		
		if( iterador != INVALID_HANDLE_VALUE && nombreArchivo != "." && nombreArchivo != ".."){
			
			string rutaArchivo = nombreDirectorio + "\\" + nombreArchivo;
			
			if( archivo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				//Busca eliminar el directorio hijo
				eliminarDirectoriosDeDirectorios(rutaArchivo);
			}else{
				//Elimina archivos del directorio lleno
				DeleteFile(rutaArchivo.c_str());
			}
		}
	}while(FindNextFile(iterador, &archivo) != 0);
	FindClose(iterador);
	
	//Elimina el directorio padre
	RemoveDirectory(nombreDirectorio.c_str());
}